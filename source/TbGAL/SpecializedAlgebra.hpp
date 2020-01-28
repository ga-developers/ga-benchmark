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

#define TBGAL_DEFAULT_SCALAR_TYPE gabm::real_t

#include <tbgal/using_Eigen.hpp>
using namespace tbgal;

#if GABM_CHECK_MODEL(ConformalModel)

    #define TBGAL_ConformalD_BaseSpaceDimensions GABM_D_DIMENSIONS
    #include <tbgal/assuming_ConformalD.hpp>
    using namespace tbgal::ConformalD;

#elif GABM_CHECK_MODEL(EuclideanModel)

    #define TBGAL_EuclideanD_BaseSpaceDimensions GABM_D_DIMENSIONS
    #include <tbgal/assuming_EuclideanD.hpp>
    using namespace tbgal::EuclideanD;

#elif GABM_CHECK_MODEL(HomogeneousModel)

    #define TBGAL_HomogeneousD_BaseSpaceDimensions GABM_D_DIMENSIONS
    #include <tbgal/assuming_HomogeneousD.hpp>
    using namespace tbgal::HomogeneousD;

#elif GABM_CHECK_MODEL(MinkowskiModel)

    #define TBGAL_MinkowskiD_BaseSpaceDimensions GABM_D_DIMENSIONS
    #include <tbgal/assuming_MinkowskiD.hpp>
    using namespace tbgal::MinkowskiD;

#endif

#endif // __GABM_SPECIALIZED_ALGEBRA_HPP__
