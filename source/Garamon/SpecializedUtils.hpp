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

inline Mvec<gabm::real_t> _garamon_MakeBladeFactorImpl(gabm::vector_coords_t const &coords) {
    Mvec<gabm::real_t> result;
    for (std::size_t i = 0; i != coords.size(); ++i) {
        result[1u << i] = coords[i];
    }
    return result;
}

GABM_DEFINE_MAKE_BLADE(scalar_factor, vector_factors, grade) {
    Mvec<gabm::real_t> result(scalar_factor);
    for (auto const &coords : vector_factors) {
        result ^= _garamon_MakeBladeFactorImpl(coords);
    }
    return result;
}

GABM_DEFINE_SQUARED_REVERSE_NORM(arg, grade) {
    return arg.quadraticNorm();
}

#endif // __GABM_SPECIALIZED_UTILS_HPP__
