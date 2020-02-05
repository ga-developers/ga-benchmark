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

inline vector_t _versor_MakeBladeFactorImpl(gabm::vector_coords_t const &coords) {
    vector_t result;
    for (std::size_t i = 0; i != coords.size(); ++i) {
        result[i] = coords[i];
    }
    return result;
}

template<std::size_t... Indices>
inline decltype(auto) _versor_MakeBladeImpl(gabm::real_t scalar_factor, gabm::factors_list_t vector_factors, std::index_sequence<Indices...>) {
    return (_versor_MakeBladeFactorImpl(vector_factors[Indices]) ^ ... ^ scalar_t(scalar_factor));
}

GABM_DEFINE_MAKE_BLADE(scalar_factor, vector_factors, grade) {
    return _versor_MakeBladeImpl(scalar_factor, vector_factors, std::make_index_sequence<grade>{});
}

GABM_DEFINE_SQUARED_REVERSE_NORM(arg, grade) {
    return arg.rwt();
}

#endif // __GABM_SPECIALIZED_UTILS_HPP__
