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
along with GA-Benchmark. If not, see < https://www.gnu.org/licenses/>.
/**/

#ifndef __GABENCHMARK_SPECIALIZED_ALGEBRA_HPP__
#define __GABENCHMARK_SPECIALIZED_ALGEBRA_HPP__

#include <ga/core.hpp>
#include <ga/util.hpp>
#include <ga/extra.hpp>

#if GABENCHMARK_CHECK_MODEL(EuclideanModel)

    #include <ga/model/euclidean.hpp>

    namespace gabenchmark {

        using namespace ga;

        _GA_EUCLIDEAN_ALGEBRA_DEFINITION(space, basis_vectors_names, (GABENCHMARK_D_DIMENSIONS))
        _GA_CORE_OVERLOAD(space)
        _GA_UTIL_OVERLOAD(space)
        _GA_EXTRA_OVERLOAD(space, basis_vectors_names)
        _GA_EUCLIDEAN_ALGEBRA_OVERLOAD(space)

    }

#elif GABENCHMARK_CHECK_MODEL(ConformalModel)

    #include <ga/model/conformal.hpp>

    namespace gabenchmark {

        using namespace ga;

        _GA_CONFORMAL_ALGEBRA_DEFINITION(space, basis_vectors_names, (GABENCHMARK_D_DIMENSIONS))
        _GA_CORE_OVERLOAD(space)
        _GA_UTIL_OVERLOAD(space)
        _GA_EXTRA_OVERLOAD(space, basis_vectors_names)
        _GA_CONFORMAL_ALGEBRA_OVERLOAD(space)

    }

#elif GABENCHMARK_CHECK_MODEL(HomogeneousModel)

    #include <ga/model/homogeneous.hpp>

    namespace gabenchmark {

        using namespace ga;

        _GA_HOMOGENEOUS_ALGEBRA_DEFINITION(space, basis_vectors_names, (GABENCHMARK_D_DIMENSIONS))
        _GA_CORE_OVERLOAD(space)
        _GA_UTIL_OVERLOAD(space)
        _GA_EXTRA_OVERLOAD(space, basis_vectors_names)
        _GA_HOMOGENEOUS_ALGEBRA_OVERLOAD(space)

    }

#elif GABENCHMARK_CHECK_MODEL(MinkowskiModel)

    #include <ga/model/minkowski.hpp>

    namespace gabenchmark {

        using namespace ga;

        _GA_MINKOWSKI_ALGEBRA_DEFINITION(space, basis_vectors_names, (GABENCHMARK_D_DIMENSIONS))
        _GA_CORE_OVERLOAD(space)
        _GA_UTIL_OVERLOAD(space)
        _GA_EXTRA_OVERLOAD(space, basis_vectors_names)
        _GA_MINKOWSKI_ALGEBRA_OVERLOAD(space)

    }

#elif GABENCHMARK_CHECK_MODEL(SignedModel)

    #include <ga/model/signed/metric_space.hpp>
    #include <ga/model/signed/macro_for_algebra_definition.hpp>

    namespace gabenchmark {

        using namespace ga;

        _GA_SIGNED_ALGEBRA_DEFINITION(space, basis_vectors_names, (GABENCHMARK_P_DIMENSIONS), (GABENCHMARK_Q_DIMENSIONS))
        _GA_CORE_OVERLOAD(space)
        _GA_UTIL_OVERLOAD(space)
        _GA_EXTRA_OVERLOAD(space, basis_vectors_names)

    }

#endif

#endif // __GABENCHMARK_SPECIALIZED_ALGEBRA_HPP__
