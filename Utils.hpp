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

#ifndef __GABM_UTILS_HPP__
#define __GABM_UTILS_HPP__

template<gabm::grade_t Grade>
decltype(auto) MakeBlade(gabm::real_t, gabm::factors_list_t const &);

template<gabm::grade_t Grade, typename ArgumentType>
gabm::real_t SquaredReverseNorm(ArgumentType const &);

namespace gabm {

    const static real_t pi = std::acos(static_cast<real_t>(-1));
    const static real_t two_pi = 2 * pi;

    real_t MakeRandomAngle(std::default_random_engine &random_engine) {
        static std::uniform_real_distribution<real_t> uniform_distribution(0, two_pi);
        return uniform_distribution(random_engine);
    }

    template<grade_t Grade>
    decltype(auto) MakeRandomBlade(std::default_random_engine &random_engine) {
        static std::uniform_real_distribution<real_t> uniform_distribution(-1, +1);

        real_t scalar = uniform_distribution(random_engine);

        factors_list_t factors;
        factors.reserve(Grade);
        for (std::size_t factor_ind = 0; factor_ind != Grade; ++factor_ind) {
            vector_coords_t factor{};
            factor[factor_ind] = 1;
            for (std::size_t coord_ind = Grade; coord_ind != GABM_N_DIMENSIONS; ++coord_ind) {
                factor[coord_ind] = uniform_distribution(random_engine);
            }
            factors.push_back(factor);
        }

        return MakeBlade<Grade>(scalar, factors);
    }

    template<grade_t Grade>
    decltype(auto) MakeRandomInvertibleBlade(std::default_random_engine &random_engine) {
        auto result = MakeRandomBlade<Grade>(random_engine);
        while (std::abs(SquaredReverseNorm<Grade>(result)) <= GABM_ZERO_TOLERANCE) {
            result = MakeRandomBlade<Grade>(random_engine);
        }
        return result;
    }

}

#define GABM_DEFINE_MAKE_BLADE(SCALAR_FACTOR, VECTOR_FACTORS, GRADE) \
    template<gabm::grade_t GRADE> \
    decltype(auto) MakeBlade(gabm::real_t SCALAR_FACTOR, gabm::factors_list_t const &VECTOR_FACTORS)

#define GABM_DEFINE_SQUARED_REVERSE_NORM(ARG, GRADE) \
    template<gabm::grade_t GRADE, typename ArgumentType> \
    gabm::real_t SquaredReverseNorm(ArgumentType const &ARG)

#include <SpecializedUtils.hpp>

#endif // __GABM_UTILS_HPP__
