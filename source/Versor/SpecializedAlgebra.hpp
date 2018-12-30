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

#include <vsr/detail/vsr_multivector.h>

namespace gabenchmark {

    using namespace vsr;

#if GABENCHMARK_CHECK_MODEL(ConformalModel)

    using algebra_t = algebra<metric<(GABENCHMARK_D_DIMENSIONS) + 1, 1, true>, real_t>;

#elif GABENCHMARK_CHECK_MODEL(EuclideanModel)

    using algebra_t = algebra<metric<(GABENCHMARK_D_DIMENSIONS)>, real_t>;

#elif GABENCHMARK_CHECK_MODEL(HomogeneousModel)

    using algebra_t = algebra<metric<(GABENCHMARK_D_DIMENSIONS) + 1>, real_t>;

#elif GABENCHMARK_CHECK_MODEL(MinkowskiModel)

    using algebra_t = algebra<metric<(GABENCHMARK_D_DIMENSIONS) + 1, 1>, real_t>;

#endif

    using scalar_t = algebra_t::mv_t<algebra_t::types::sca>;
    using vector_t = algebra_t::mv_t<algebra_t::types::vec>;

}

#endif // __GABENCHMARK_SPECIALIZED_ALGEBRA_HPP__
