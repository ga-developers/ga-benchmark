/* Copyright(C) ga-developers
 *
 * Repository: https://github.com/ga-developers/ga-benchmark.git
 * 
 * This file is part of the GA-Benchmark project.
 * 
 * GA-Benchmark is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * GA-Benchmark is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GA-Benchmark. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef __GABM_SPECIALIZED_ALGEBRA_COMMONS_HPP__
#define __GABM_SPECIALIZED_ALGEBRA_COMMONS_HPP__

#include <glucat/glucat.h>

typedef glucat::tuning<
    glucat::DEFAULT_Mult_Matrix_Threshold,
    glucat::DEFAULT_Div_Max_Steps,
    glucat::DEFAULT_Sqrt_Max_Steps,
    glucat::DEFAULT_Log_Max_Outer_Steps,
    glucat::DEFAULT_Log_Max_Inner_Steps,
    glucat::DEFAULT_Basis_Max_Count,
    glucat::DEFAULT_Fast_Size_Threshold,
    glucat::DEFAULT_Inv_Fast_Dim_Threshold,
    glucat::DEFAULT_Products_Size_Threshold,
    glucat::precision_promoted
> Tune_P;

#include <glucat/glucat_imp.h>
using namespace glucat;

#if GABM_CHECK_MODEL(ConformalModel)

    // GluCat requires mapping from Minkoski to Conformal and vice-versa.

    #if GABM_CHECK_OPERATION(BinaryOperations) || GABM_CHECK_OPERATION(UnaryOperations)

        // Only native implementations of the model are considered for binary and unary operations.
        #define GABM_MODEL_NOT_IMPLEMENTED

        #define GABM_GLUCAT_NEGATIVE_GENERATORS 0
        #define GABM_GLUCAT_POSITIVE_GENERATORS 0

    #else

        #define GABM_GLUCAT_NEGATIVE_GENERATORS 1
        #define GABM_GLUCAT_POSITIVE_GENERATORS ((GABM_D_DIMENSIONS) + 1)

    #endif

#elif GABM_CHECK_MODEL(EuclideanModel)

    #define GABM_GLUCAT_NEGATIVE_GENERATORS 0
    #define GABM_GLUCAT_POSITIVE_GENERATORS (GABM_D_DIMENSIONS)

#elif GABM_CHECK_MODEL(HomogeneousModel)

    #define GABM_GLUCAT_NEGATIVE_GENERATORS 0
    #define GABM_GLUCAT_POSITIVE_GENERATORS ((GABM_D_DIMENSIONS) + 1)

#elif GABM_CHECK_MODEL(MinkowskiModel)

    #define GABM_GLUCAT_NEGATIVE_GENERATORS 1
    #define GABM_GLUCAT_POSITIVE_GENERATORS ((GABM_D_DIMENSIONS) + 1)

#endif

#if (GABM_GLUCAT_POSITIVE_GENERATORS <= 4)
    #define GABM_GLUCAT_LO (-4)
    #define GABM_GLUCAT_HI (4)
#elif (GABM_GLUCAT_POSITIVE_GENERATORS <= 8)
    #define GABM_GLUCAT_LO (-8)
    #define GABM_GLUCAT_HI (8)
#else
    #define GABM_GLUCAT_LO (DEFAULT_LO)
    #define GABM_GLUCAT_HI (DEFAULT_HI)
#endif

    using multivector_t = GLUCAT_MULTIVECTOR_TYPE<gabm::real_t, GABM_GLUCAT_LO, GABM_GLUCAT_HI>;
    using scalar_t = multivector_t::scalar_t;

    inline multivector_t e(gabm::dims_t const index) noexcept {
        return multivector_t(multivector_t::index_set_t(index <= GABM_GLUCAT_POSITIVE_GENERATORS ? index : (GABM_GLUCAT_POSITIVE_GENERATORS - index)));
    }

#if GABM_D_DIMENSIONS >= 1
    static auto const e1 = e(1);
#endif

#if GABM_D_DIMENSIONS >= 2
    static auto const e2 = e(2);
#endif

#if GABM_D_DIMENSIONS >= 3
    static auto const e3 = e(3);
#endif

#if (GABM_CHECK_MODEL(MinkowskiModel) || GABM_CHECK_MODEL(ConformalModel)) && !defined(GABM_MODEL_NOT_IMPLEMENTED)

    static auto const ep = e(GABM_D_DIMENSIONS + 1);
    static auto const em = e(GABM_D_DIMENSIONS + 2);
    static auto const no = (em - ep) * 0.5;
    static auto const ni = ep + em;

    inline multivector_t pseudoscalar() noexcept {
        multivector_t result = e(1);
        for (gabm::dims_t i = 2; i <= GABM_D_DIMENSIONS; ++i) {
            result ^= e(i);
        }
        result ^= no;
        result ^= ni;
        return result;
    }

    static auto const I = pseudoscalar();
    static auto const invI = I.inv();

    template<typename... Types>
    inline multivector_t euclidean_vector(Types &&... coords) noexcept {
        std::array<gabm::real_t, GABM_D_DIMENSIONS> const coords_{ std::move(coords)... };
        multivector_t result;
        for (gabm::dims_t i = 1; i <= GABM_D_DIMENSIONS; ++i) {
            result += coords_[i - 1] * e(i);
        }
        return result;
    }

    template<typename... Types>
    inline multivector_t point(Types &&... coords) noexcept {
        auto const x = euclidean_vector(std::move(coords)...);
        return x + no + ((x % x) * 0.5) * ni;
    }

    inline multivector_t dual(multivector_t const &arg) noexcept {
        return arg % invI;
    }

    inline multivector_t undual(multivector_t const &arg) noexcept {
        return arg % I;
    }

    inline multivector_t unit(multivector_t const &arg) noexcept {
        return arg / sqrt(arg % arg.reverse()).scalar();
    }

    inline decltype(auto) apply_rotor(multivector_t const &rotor, multivector_t const &arg) noexcept {
        return rotor * arg * rotor.reverse();
    }

#endif

#endif // __GABM_SPECIALIZED_ALGEBRA_COMMONS_HPP__
