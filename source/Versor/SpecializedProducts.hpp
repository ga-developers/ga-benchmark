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

#ifndef __GABENCHMARK_SPECIALIZED_PRODUCTS_HPP__
#define __GABENCHMARK_SPECIALIZED_PRODUCTS_HPP__

namespace gabenchmark {

    #define GABENCHMARK_DOES_NOT_IMPLEMENT_DotProduct

    #define GABENCHMARK_IMPLEMENTS_GeometricProduct
    template<typename LeftArgument, typename RightArgument>
    constexpr decltype(auto) GeometricProduct(LeftArgument const &lhs, RightArgument const &rhs) {
        return lhs * rhs;
    }

    #define GABENCHMARK_DOES_NOT_IMPLEMENT_HestenesInnerProduct

    #define GABENCHMARK_IMPLEMENTS_LeftContraction
    template<typename LeftArgument, typename RightArgument>
    constexpr decltype(auto) LeftContraction(LeftArgument const &lhs, RightArgument const &rhs) {
       return lhs <= rhs;
    }

    #define GABENCHMARK_IMPLEMENTS_OuterProduct
    template<typename LeftArgument, typename RightArgument>
    constexpr decltype(auto) OuterProduct(LeftArgument const &lhs, RightArgument const &rhs) {
        return lhs ^ rhs;
    }

    #define GABENCHMARK_DOES_NOT_IMPLEMENT_RightContraction

    #define GABENCHMARK_DOES_NOT_IMPLEMENT_RegressiveProduct

    #define GABENCHMARK_DOES_NOT_IMPLEMENT_ScalarProduct

}

#endif // __GABENCHMARK_SPECIALIZED_PRODUCTS_HPP__
