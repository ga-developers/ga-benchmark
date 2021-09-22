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

#define GA_DEFAULT_FLOATING_POINT_TYPE gabm::real_t

#if GABM_D_DIMENSIONS == 1
    #define GABM_GATL_BASE_BASIS_VECTORS_NAMES "e1"
#elif GABM_D_DIMENSIONS == 2
    #define GABM_GATL_BASE_BASIS_VECTORS_NAMES "e1", "e2"
#elif GABM_D_DIMENSIONS == 3
    #define GABM_GATL_BASE_BASIS_VECTORS_NAMES "e1", "e2", "e3"
#elif GABM_D_DIMENSIONS == 4
    #define GABM_GATL_BASE_BASIS_VECTORS_NAMES "e1", "e2", "e3", "e4"
#elif GABM_D_DIMENSIONS == 5
    #define GABM_GATL_BASE_BASIS_VECTORS_NAMES "e1", "e2", "e3", "e4", "e5"
#elif GABM_D_DIMENSIONS == 6
    #define GABM_GATL_BASE_BASIS_VECTORS_NAMES "e1", "e2", "e3", "e4", "e5", "e6"
#elif GABM_D_DIMENSIONS == 7
    #define GABM_GATL_BASE_BASIS_VECTORS_NAMES "e1", "e2", "e3", "e4", "e5", "e6", "e7"
#elif GABM_D_DIMENSIONS == 8
    #define GABM_GATL_BASE_BASIS_VECTORS_NAMES "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8"
#elif GABM_D_DIMENSIONS == 9
    #define GABM_GATL_BASE_BASIS_VECTORS_NAMES "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8", "e9"
#elif GABM_D_DIMENSIONS == 10
    #define GABM_GATL_BASE_BASIS_VECTORS_NAMES "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8", "e9", "e10"
#else
    #error Update the "source/GATL/SpecializedAlgebra.hpp" file if you want to setup the benchmark with GABM_D_DIMENSIONS > 10.
#endif

#include <gatl/ga/core.hpp>
#include <gatl/ga/util.hpp>
#include <gatl/ga/extra.hpp>

using namespace ga;

#if GABM_CHECK_MODEL(ConformalModel)

    #include <gatl/ga/model/conformal.hpp>

    _GA_CONFORMAL_ALGEBRA_DEFINITION(space, basis_vectors_names, GABM_D_DIMENSIONS, GABM_GATL_BASE_BASIS_VECTORS_NAMES)
    _GA_CONFORMAL_ALGEBRA_OVERLOAD(space)

    #include <gatl/ga/model/euclidean.hpp>

    namespace euclidean {

        _GA_EUCLIDEAN_ALGEBRA_DEFINITION(space, basis_vectors_names, GABM_N_DIMENSIONS, GABM_GATL_BASE_BASIS_VECTORS_NAMES)
        _GA_CORE_OVERLOAD(space)
        _GA_UTIL_OVERLOAD(space)
        _GA_EXTRA_OVERLOAD(space, basis_vectors_names)

    }

#elif GABM_CHECK_MODEL(EuclideanModel)

    #include <gatl/ga/model/euclidean.hpp>
    _GA_EUCLIDEAN_ALGEBRA_DEFINITION(space, basis_vectors_names, GABM_D_DIMENSIONS, GABM_GATL_BASE_BASIS_VECTORS_NAMES)
    _GA_EUCLIDEAN_ALGEBRA_OVERLOAD(space)

#elif GABM_CHECK_MODEL(HomogeneousModel)

    #include <gatl/ga/model/homogeneous.hpp>
    _GA_HOMOGENEOUS_ALGEBRA_DEFINITION(space, basis_vectors_names, GABM_D_DIMENSIONS, GABM_GATL_BASE_BASIS_VECTORS_NAMES)
    _GA_HOMOGENEOUS_ALGEBRA_OVERLOAD(space)

#elif GABM_CHECK_MODEL(MinkowskiModel)

    #include <gatl/ga/model/minkowski.hpp>
    _GA_MINKOWSKI_ALGEBRA_DEFINITION(space, basis_vectors_names, GABM_D_DIMENSIONS, GABM_GATL_BASE_BASIS_VECTORS_NAMES)
    _GA_MINKOWSKI_ALGEBRA_OVERLOAD(space)

    #include <gatl/ga/model/euclidean.hpp>

    namespace euclidean {

        _GA_EUCLIDEAN_ALGEBRA_DEFINITION(space, basis_vectors_names, GABM_N_DIMENSIONS, GABM_GATL_BASE_BASIS_VECTORS_NAMES)
        _GA_CORE_OVERLOAD(space)
        _GA_UTIL_OVERLOAD(space)
        _GA_EXTRA_OVERLOAD(space, basis_vectors_names)

    }

#endif

_GA_CORE_OVERLOAD(space)
_GA_UTIL_OVERLOAD(space)
_GA_EXTRA_OVERLOAD(space, basis_vectors_names)

#endif // __GABM_SPECIALIZED_ALGEBRA_HPP__
