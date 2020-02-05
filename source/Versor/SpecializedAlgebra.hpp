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

#ifndef __GABM_SPECIALIZED_ALGEBRA_HPP__
#define __GABM_SPECIALIZED_ALGEBRA_HPP__

#include <vsr/detail/vsr_multivector.h>
using namespace vsr;

#if GABM_CHECK_MODEL(ConformalModel)

    #if GABM_D_DIMENSIONS == 2

        #include <vsr/space/vsr_cga2D.h>

        using algebra_t = algebra<metric<(GABM_D_DIMENSIONS) + 1, 1, true>, gabm::real_t>;

        static auto const e1 = cga2D::Vec(1, 0);
        static auto const e2 = cga2D::Vec(0, 1);
        static auto const no = cga2D::Ori(1);
        static auto const ni = cga2D::Inf(1);

    #elif GABM_D_DIMENSIONS == 3

        #include <vsr/space/vsr_cga3D.h>

        using algebra_t = algebra<metric<(GABM_D_DIMENSIONS) + 1, 1, true>, gabm::real_t>;
        
        static auto const e1 = cga::Vec(1, 0, 0);
        static auto const e2 = cga::Vec(0, 1, 0);
        static auto const e3 = cga::Vec(0, 0, 1);
        static auto const no = cga::Ori(1);
        static auto const ni = cga::Inf(1);

    #endif
        
#elif GABM_CHECK_MODEL(EuclideanModel)

    using algebra_t = algebra<metric<(GABM_D_DIMENSIONS)>, gabm::real_t>;

#elif GABM_CHECK_MODEL(HomogeneousModel)

    using algebra_t = algebra<metric<(GABM_D_DIMENSIONS) + 1>, gabm::real_t>;

#elif GABM_CHECK_MODEL(MinkowskiModel)

    using algebra_t = algebra<metric<(GABM_D_DIMENSIONS) + 1, 1>, gabm::real_t>;

#endif

template<bits::type K>
using kvector_t = algebra_t::mv_t<typename blade<GABM_N_DIMENSIONS, K>::type>;

using scalar_t = kvector_t<0>;
using vector_t = kvector_t<1>;

#endif // __GABM_SPECIALIZED_ALGEBRA_HPP__
