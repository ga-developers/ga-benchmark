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

#ifndef __GABENCHMARK_SPECIALIZED_ALGEBRA_HPP__
#define __GABENCHMARK_SPECIALIZED_ALGEBRA_HPP__

namespace gabenchmark {

    namespace detail {

        constexpr std::uint64_t binomial_coefficient(dims_t const n, dims_t const k) {
            return k != 0 && k != n ? (binomial_coefficient(n - 1, k - 1) + binomial_coefficient(n - 1, k)) : 1;
        }

    }

    template<grade_t K>
    using kvector_t = std::array<real_t, detail::binomial_coefficient(GABENCHMARK_N_DIMENSIONS, K)>;

}

#endif // __GABENCHMARK_SPECIALIZED_ALGEBRA_HPP__
