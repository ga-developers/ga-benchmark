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

#ifndef __GABM_TYPES_HPP__
#define __GABM_TYPES_HPP__

#include <array>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <random>
#include <vector>

#include <benchmark/benchmark.h>

namespace gabm {

    using real_t = std::double_t;

    using grade_t = std::int32_t;
    using dims_t = std::uint32_t;

    using vector_coords_t = std::array<real_t, GABM_N_DIMENSIONS>;
    using factors_list_t = std::vector<vector_coords_t>;

    namespace detail {

        std::default_random_engine random_engine{ GABM_OPERATION }; /*The seed is constant because all solutions must use the same set of random numbers.*/
    
    }

    template<typename RandomEntryGeneratorClass>
    class RandomEntries {
    private:

        using entry_type = decltype(RandomEntryGeneratorClass::MakeRandomEntry(detail::random_engine));
        using container_type = std::vector<entry_type>;

    public:

        using size_type = typename container_type::size_type;
        using value_type = typename container_type::value_type;
        using reference = typename container_type::reference;
        using const_reference = typename container_type::const_reference;

        RandomEntries() :
            entries_() {
            entries_.reserve(GABM_ITERATIONS);
            for (std::size_t ind = 0; ind != (GABM_ITERATIONS); ++ind) {
                entries_.push_back(RandomEntryGeneratorClass::MakeRandomEntry(detail::random_engine));
            }
        }

        GABM_ALWAYS_INLINE size_type size() const {
            return entries_.size();
        }
        
        GABM_ALWAYS_INLINE reference operator[](size_type ind) {
            return entries_[ind];
        }

        GABM_ALWAYS_INLINE const_reference operator[](size_type ind) const {
            return entries_[ind];
        }

    private:

        container_type entries_;
    };

}

#endif // __GABM_TYPES_HPP__
