/**
Copyright(C) 2018 ga-developers

Repository: https://github.com/ga-developers/ga-benchmark.git

This file is part of the GA-Benchmark project.

GA-Benchmark is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

GA-Benchmark is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GA-Benchmark. If not, see <https://www.gnu.org/licenses/>.
/**/

#ifndef __GABENCHMARK_SPECIALIZED_ALGEBRA_COMMONS_HPP__
#define __GABENCHMARK_SPECIALIZED_ALGEBRA_COMMONS_HPP__

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

namespace gabenchmark {

    using namespace glucat;

#if GABENCHMARK_CHECK_MODEL(ConformalModel)

    // GluCat requires mapping from Minkoski to Conformal and vice-versa.

    #if GABENCHMARK_CHECK_OPERATION(Products)

        // For products, only native implementations of the model are considered.
        #define GABENCHMARK_DOES_NOT_IMPLEMENT_THE_MODEL

        #define GABENCHMARK_GLUCAT_NEGATIVE_GENERATORS 0
        #define GABENCHMARK_GLUCAT_POSITIVE_GENERATORS 0

    #else

        #define GABENCHMARK_GLUCAT_NEGATIVE_GENERATORS 1
        #define GABENCHMARK_GLUCAT_POSITIVE_GENERATORS ((GABENCHMARK_D_DIMENSIONS) + 1)

    #endif

#elif GABENCHMARK_CHECK_MODEL(EuclideanModel)

    #define GABENCHMARK_GLUCAT_NEGATIVE_GENERATORS 0
    #define GABENCHMARK_GLUCAT_POSITIVE_GENERATORS (GABENCHMARK_D_DIMENSIONS)

#elif GABENCHMARK_CHECK_MODEL(HomogeneousModel)

    #define GABENCHMARK_GLUCAT_NEGATIVE_GENERATORS 0
    #define GABENCHMARK_GLUCAT_POSITIVE_GENERATORS ((GABENCHMARK_D_DIMENSIONS) + 1)

#elif GABENCHMARK_CHECK_MODEL(MinkowskiModel)

    #define GABENCHMARK_GLUCAT_NEGATIVE_GENERATORS 1
    #define GABENCHMARK_GLUCAT_POSITIVE_GENERATORS ((GABENCHMARK_D_DIMENSIONS) + 1)

#endif

#if (GABENCHMARK_GLUCAT_POSITIVE_GENERATORS <= 4)
    #define GABENCHMARK_GLUCAT_LO (-4)
    #define GABENCHMARK_GLUCAT_HI (4)
#elif (GABENCHMARK_GLUCAT_POSITIVE_GENERATORS <= 8)
    #define GABENCHMARK_GLUCAT_LO (-8)
    #define GABENCHMARK_GLUCAT_HI (8)
#else
    #define GABENCHMARK_GLUCAT_LO (DEFAULT_LO)
    #define GABENCHMARK_GLUCAT_HI (DEFAULT_HI)
#endif

    using multivector_t = GLUCAT_MULTIVECTOR_TYPE<real_t, GABENCHMARK_GLUCAT_LO, GABENCHMARK_GLUCAT_HI>;
    using scalar_t = multivector_t::scalar_t;

    inline multivector_t e(dims_t const index) noexcept {
        return multivector_t(multivector_t::index_set_t(index <= GABENCHMARK_GLUCAT_POSITIVE_GENERATORS ? index : (GABENCHMARK_GLUCAT_POSITIVE_GENERATORS - index)));
    }

#if GABENCHMARK_D_DIMENSIONS >= 1
    static auto const e1 = e(1);
#endif

#if GABENCHMARK_D_DIMENSIONS >= 2
    static auto const e2 = e(2);
#endif

#if GABENCHMARK_D_DIMENSIONS >= 3
    static auto const e3 = e(3);
#endif

#if GABENCHMARK_CHECK_MODEL(ConformalModel) && !defined(GABENCHMARK_DOES_NOT_IMPLEMENT_THE_MODEL)

    static auto const ep = e(GABENCHMARK_D_DIMENSIONS + 1);
    static auto const em = e(GABENCHMARK_D_DIMENSIONS + 2);
    static auto const no = (em - ep) * 0.5;
    static auto const ni = ep + em;

    inline multivector_t pseudoscalar() noexcept {
        multivector_t result = e(1);
        for (dims_t i = 2; i <= GABENCHMARK_D_DIMENSIONS; ++i) {
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
        std::array<real_t, GABENCHMARK_D_DIMENSIONS> const coords_{ std::move(coords)... };
        multivector_t result;
        for (dims_t i = 1; i <= GABENCHMARK_D_DIMENSIONS; ++i) {
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

}

#endif // __GABENCHMARK_SPECIALIZED_ALGEBRA_COMMONS_HPP__
