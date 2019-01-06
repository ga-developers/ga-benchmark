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

#ifndef __GABENCHMARK_SPECIALIZED_UTILS_HPP__
#define __GABENCHMARK_SPECIALIZED_UTILS_HPP__

namespace gabenchmark {

    template<typename Scalar>
    constexpr Scalar MakeScalar(Scalar const &scalar) {
        return scalar;
    }

    namespace detail {

        template<std::size_t Index>
        struct MakeVectorImpl {
            template<typename Coordinates>
            static constexpr decltype(auto) Eval(Coordinates const &coords) {
                return MakeVectorImpl<Index - 1>::Eval(coords) + coords[Index] * e(c<Index + 1>);
            }
        };
        
        template<>
        struct MakeVectorImpl<0> {
            template<typename Coordinates>
            static constexpr decltype(auto) Eval(Coordinates const &coords) {
                return coords[0] * e(c<1>);
            }
        };

    }

    template<dims_t Dimensions, typename Coordinates>
    constexpr decltype(auto) MakeVector(Coordinates const &coords) {
        return detail::MakeVectorImpl<Dimensions - 1>::Eval(coords);
    }

    namespace detail {

        template<grade_t Grade>
        struct MakeBladeImpl {
            template<dims_t Dimensions, typename Scalar, typename Factors>
            static constexpr decltype(auto) Eval(Scalar const &scalar, Factors const &factors) {
                return op(MakeBladeImpl<Grade - 1>::template Eval<Dimensions>(scalar, factors), MakeVector<Dimensions>(factors[Grade - 1]));
            }
        };

        template<>
        struct MakeBladeImpl<0> {
            template<dims_t Dimensions, typename Scalar, typename Factors>
            static constexpr decltype(auto) Eval(Scalar const &scalar, Factors const &) {
                return MakeScalar(scalar);
            }
        };

    }

    template<grade_t Grade, dims_t Dimensions, typename Scalar, typename Factors>
    constexpr decltype(auto) MakeBlade(Scalar const &scalar, Factors const &factors) {
        return detail::MakeBladeImpl<Grade>::template Eval<Dimensions>(scalar, factors);
    }

}

#endif // __GABENCHMARK_SPECIALIZED_UTILS_HPP__
