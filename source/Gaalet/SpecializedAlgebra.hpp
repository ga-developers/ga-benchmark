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

#ifndef __GABM_SPECIALIZED_ALGEBRA_HPP__
#define __GABM_SPECIALIZED_ALGEBRA_HPP__

#include <utility>
#include <gaalet.h>

using namespace gaalet;

#if GABM_CHECK_MODEL(ConformalModel)

    // Gaalet requires mapping from Minkoski to Conformal and vice-versa.

    #if GABM_CHECK_OPERATION(BinaryOperations) || GABM_CHECK_OPERATION(UnaryOperations)

        // Only native implementations of the model are considered for binary and unary operations.
        #define GABM_MODEL_NOT_IMPLEMENTED

    #else

        using space = algebra<signature<(GABM_D_DIMENSIONS) + 1, 1>, gabm::real_t>;

    #endif

#elif GABM_CHECK_MODEL(EuclideanModel)

    using space = algebra<signature<GABM_D_DIMENSIONS, 0>, gabm::real_t>;

#elif GABM_CHECK_MODEL(HomogeneousModel)

    using space = algebra<signature<(GABM_D_DIMENSIONS) + 1, 0>, gabm::real_t>;

#elif GABM_CHECK_MODEL(MinkowskiModel)

    using space = algebra<signature<(GABM_D_DIMENSIONS) + 1, 1>, gabm::real_t>;

#endif

#if !defined(GABM_MODEL_NOT_IMPLEMENTED)

    // Helper function to access the coefficients of the multivector.
    template<std::size_t... Indices, typename Type>
    inline decltype(auto) element(Type const &arg) noexcept {
        return arg.template element<((1 << (Indices - 1)) | ... | 0)>();
    }

    // Helper function to define scalar values.
    template<typename Type>
    inline decltype(auto) svalue(Type const &value) noexcept {
        using result_t = typename space::mv<0>::type;
        return result_t(value);
    }

    // Helper function to define unit basis vectors (the first index is 1).
    template<std::size_t Index>
    inline decltype(auto) e() noexcept {
        using result_t = typename space::mv<(1 << (Index - 1))>::type;
        return result_t(1);
    }

    // Helper function to define vectors.
    template<typename IndexSequence>
    struct _gaalet_vector_impl;

    template<std::size_t... Indices>
    struct _gaalet_vector_impl<std::index_sequence<Indices...> > {
        using type = typename space::mv<(1 << Indices)...>::type;
    };

    template<typename... Types>
    inline decltype(auto) vector(Types &&... coords) noexcept {
        static_assert(GABM_N_DIMENSIONS == sizeof...(Types), "The number of coordinates must be equal to the number of dimensions of the vector space.");
        using result_t = typename _gaalet_vector_impl<std::make_index_sequence<GABM_N_DIMENSIONS> >::type;
        return result_t(std::move(coords)...);
    }

    // Other constant values and helper functions.
    #if GABM_D_DIMENSIONS >= 1
        static auto const e1 = e<1>();
    #endif

    #if GABM_D_DIMENSIONS >= 2
        static auto const e2 = e<2>();
    #endif

    #if GABM_D_DIMENSIONS >= 3
        static auto const e3 = e<3>();
    #endif

    template<typename RotorType, typename ArgumentType>
    inline decltype(auto) apply_rotor(RotorType const &rotor, ArgumentType const &arg) noexcept {
        return eval(rotor * arg * (~rotor));
    }

#endif

#if (GABM_CHECK_MODEL(MinkowskiModel) || GABM_CHECK_MODEL(ConformalModel)) && !defined(GABM_MODEL_NOT_IMPLEMENTED)

    static auto const ep = e<(GABM_D_DIMENSIONS) + 1>();
    static auto const em = e<(GABM_D_DIMENSIONS) + 2>();
    static auto const no = eval((em - ep) * 0.5);
    static auto const ni = eval(ep + em);

    inline decltype(auto) pseudoscalar() noexcept {
        using result_t = typename space::mv<(1 << GABM_N_DIMENSIONS) - 1>::type;
        return result_t(1);
    }

    static auto const I = pseudoscalar();
    static auto const invI = eval(!I);

    template<typename... Types>
    inline decltype(auto) euclidean_vector(Types &&... coords) noexcept {
        static_assert(GABM_D_DIMENSIONS == sizeof...(Types), "The number of coordinates must be equal to the number of dimensions of the Euclidean vector space.");
        using result_t = typename _gaalet_vector_impl<std::make_index_sequence<GABM_D_DIMENSIONS> >::type;
        return result_t(std::move(coords)...);
    }

    template<typename... Types>
    inline decltype(auto) point(Types &&... coords) noexcept {
        auto aux = ((std::move(coords) * std::move(coords)) + ... + 0);
        return vector(std::move(coords)..., (aux - 1) * 0.5, (aux + 1) * 0.5);
    }

    template<typename ArgumentType>
    inline decltype(auto) dual(ArgumentType const &arg) noexcept {
        return eval(arg * invI);
    }

    template<typename ArgumentType>
    inline decltype(auto) undual(ArgumentType const &arg) noexcept {
        return eval(arg * I);
    }

    template<typename ArgumentType>
    inline decltype(auto) unit(ArgumentType const &arg) noexcept {
        return eval((1 / sqrt(eval(arg * (~arg))[0])) * arg);
    }

#endif

#endif // __GABM_SPECIALIZED_ALGEBRA_HPP__
