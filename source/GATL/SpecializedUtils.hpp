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

#ifndef __GABENCHMARK_SPECIALIZED_UTILS_HPP__
#define __GABENCHMARK_SPECIALIZED_UTILS_HPP__

#include "SpecializedAlgebra.hpp"

namespace gabenchmark {

    namespace detail {

        template<std::size_t Index>
        struct MakeFactorImpl {
            template<typename Coordinates>
            static constexpr decltype(auto) Eval(Coordinates const &coords) {
                return MakeFactorImpl<Index - 1>::Eval(coords) + coords[Index] * e(c<Index + 1>);
            }
        };
        
        template<>
        struct MakeFactorImpl<0> {
            template<typename Coordinates>
            static constexpr decltype(auto) Eval(Coordinates const &coords) {
                return coords[0] * e(c<1>);
            }
        };

        template<std::size_t Index>
        struct MakeBladeImpl {
            template<dims_t Dimensions, typename Factors>
            static constexpr decltype(auto) Eval(Factors const &factors) {
                return op(MakeBladeImpl<Index - 1>::Eval<Dimensions>(factors), MakeFactorImpl<Dimensions - 1>::Eval(factors[Index]));
            }
        };

        template<>
        struct MakeBladeImpl<0> {
            template<dims_t Dimensions, typename Factors>
            static constexpr decltype(auto) Eval(Factors const &factors) {
                return MakeFactorImpl<Dimensions - 1>::Eval(factors[0]);
            }
        };

    }

    template<grade_t Grade, dims_t Dimensions, typename Scalar, typename Factors>
    constexpr decltype(auto) MakeBlade(Scalar const &scalar, Factors const &factors) {
        return scalar * detail::MakeBladeImpl<Grade - 1>::Eval<Dimensions>(factors);
    }

}

#endif // __GABENCHMARK_SPECIALIZED_UTILS_HPP__
