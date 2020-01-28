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

#ifndef __GABM_SPECIALIZED_UTILS_HPP__
#define __GABM_SPECIALIZED_UTILS_HPP__

#include <utility>

template<std::size_t... Indices>
constexpr decltype(auto) _gatl_MakeBladeImpl(gabm::real_t scalar_factor, gabm::factors_list_t const &vector_factors, std::index_sequence<Indices...>) noexcept {
    return (vector(vector_factors[Indices].begin(), vector_factors[Indices].end()) ^ ... ^ scalar(scalar_factor));
}

GABM_DEFINE_MAKE_BLADE(scalar_factor, vector_factors, grade) {
    return _gatl_MakeBladeImpl(scalar_factor, vector_factors, std::make_index_sequence<grade>{});
}

GABM_DEFINE_SQUARED_REVERSE_NORM(arg, grade) {
    return rnorm_sqr(arg);
}

#endif // __GABM_SPECIALIZED_UTILS_HPP__
