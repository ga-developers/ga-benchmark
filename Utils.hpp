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

#ifndef __GABENCHMARK_UTILS_HPP__
#define __GABENCHMARK_UTILS_HPP__

namespace gabenchmark {

    namespace detail {

        std::default_random_engine random_engine{ static_cast<long unsigned int>(32) }; // The seed is constant because all libraries must use the same set of random numbers.
        std::uniform_real_distribution<real_t> uniform_distribution(0, 1);

    }

    template<grade_t Grade>
    decltype(auto) MakeRandomBlade() {
        real_t scalar = detail::uniform_distribution(detail::random_engine);

        std::vector<vector_coords> factors;
        factors.reserve(Grade);
        for (std::size_t factor_ind = 0; factor_ind != Grade; ++factor_ind) {
            vector_coords factor{};
            factor[factor_ind] = 1;
            for (std::size_t coord_ind = Grade; coord_ind != GABENCHMARK_N_DIMENSIONS; ++coord_ind) {
                factor[coord_ind] = detail::uniform_distribution(detail::random_engine);
            }
            factors.push_back(factor);
        }

        return MakeBlade<Grade, GABENCHMARK_N_DIMENSIONS>(scalar, factors);
    }

}

#endif // __GABENCHMARK_UTILS_HPP__
