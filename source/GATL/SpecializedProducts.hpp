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
along with GA-Benchmark. If not, see < https://www.gnu.org/licenses/>.
/**/

#ifndef __GABENCHMARK_SPECIALIZED_PRODUCTS_HPP__
#define __GABENCHMARK_SPECIALIZED_PRODUCTS_HPP__

#include "SpecializedAlgebra.hpp"

namespace gabenchmark {

    template<typename LeftArgument, typename RightArgument>
    constexpr decltype(auto) DotProduct(LeftArgument const &lhs, RightArgument const &rhs) {
        return dot(lhs, rhs);
    }

    template<typename LeftArgument, typename RightArgument>
    constexpr decltype(auto) GeometricProduct(LeftArgument const &lhs, RightArgument const &rhs) {
        return gp(lhs, rhs);
    }

    template<typename LeftArgument, typename RightArgument>
    constexpr decltype(auto) HestenesInnerProduct(LeftArgument const &lhs, RightArgument const &rhs) {
        return hip(lhs, rhs);
    }

    template<typename LeftArgument, typename RightArgument>
    constexpr decltype(auto) LeftContraction(LeftArgument const &lhs, RightArgument const &rhs) {
        return lcont(lhs, rhs);
    }

    template<typename LeftArgument, typename RightArgument>
    constexpr decltype(auto) OuterProduct(LeftArgument const &lhs, RightArgument const &rhs) {
        return op(lhs, rhs);
    }

    template<typename LeftArgument, typename RightArgument>
    constexpr decltype(auto) RegressiveProduct(LeftArgument const &lhs, RightArgument const &rhs) {
        return rp(lhs, rhs);
    }

    template<typename LeftArgument, typename RightArgument>
    constexpr decltype(auto) RightContraction(LeftArgument const &lhs, RightArgument const &rhs) {
        return rcont(lhs, rhs);
    }

    template<typename LeftArgument, typename RightArgument>
    constexpr decltype(auto) ScalarProduct(LeftArgument const &lhs, RightArgument const &rhs) {
        return sp(lhs, rhs);
    }

}

#endif // __GABENCHMARK_SPECIALIZED_PRODUCTS_HPP__
