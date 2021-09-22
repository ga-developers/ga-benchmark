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
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include <benchmark/benchmark.h>

namespace gabm {

    using real_t = std::double_t;

    using grade_t = std::int32_t;
    using dims_t = std::uint32_t;

    using direction_coords_t = std::array<real_t, GABM_D_DIMENSIONS>;
    using vector_coords_t = std::array<real_t, GABM_N_DIMENSIONS>;
    using factors_list_t = std::vector<vector_coords_t>;

#if GABM_CHECK_MODEL(ConformalModel) || GABM_CHECK_MODEL(HomogeneousModel) || GABM_CHECK_MODEL(MinkowskiModel)
    using location_coords_t = std::array<real_t, GABM_D_DIMENSIONS>;
#endif

    class BaseEntries;
    
    namespace detail {

        std::default_random_engine random_engine{ GABM_OPERATION }; /*The seed is constant because all solutions must use the same set of random numbers.*/
        
        std::vector<BaseEntries*> entries;
    
    }

    class BaseEntries {
    public:

        BaseEntries() {
            detail::entries.push_back(this);
        }

        virtual void init() = 0;
    };

    template<typename EntryGeneratorClass>
    class Entries : public BaseEntries {
    private:

        using Super = BaseEntries;

        using entry_type = decltype(EntryGeneratorClass::MakeEntry());
        using container_type = std::vector<entry_type>;

    public:

        using size_type = typename container_type::size_type;
        using value_type = typename container_type::value_type;
        using reference = typename container_type::reference;
        using const_reference = typename container_type::const_reference;

        Entries() :
            Super(),
            _entries() {
        }

        void init() override {
            _entries.clear();
            _entries.reserve(GABM_ITERATIONS);
            for (std::size_t ind = 0; ind != (GABM_ITERATIONS); ++ind) {
                _entries.push_back(EntryGeneratorClass::MakeEntry());
            }
        }

        GABM_ALWAYS_INLINE size_type size() const {
            return _entries.size();
        }
        
        GABM_ALWAYS_INLINE reference operator[](size_type ind) {
            return _entries[ind];
        }

        GABM_ALWAYS_INLINE const_reference operator[](size_type ind) const {
            return _entries[ind];
        }

    private:

        container_type _entries;
    };

    void Initialize() {
        for (BaseEntries *ptr : detail::entries) {
            ptr->init();
        }
    }

}

#endif // __GABM_TYPES_HPP__
