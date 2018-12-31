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

#ifndef __GABENCHMARK_DECLARATIONS_HPP__
#define __GABENCHMARK_DECLARATIONS_HPP__

#include <array>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

#include <benchmark/benchmark.h>

#define ConformalModel   0x01
#define EuclideanModel   0x02
#define HomogeneousModel 0x03
#define MinkowskiModel   0x04
#define SignedModel      0x05
#define GABENCHMARK_CHECK_MODEL(MODEL) (MODEL == GABENCHMARK_MODEL)

#define Products    0x11
#define GABENCHMARK_CHECK_OPERATION(OPERATION) (OPERATION == GABENCHMARK_OPERATION)

#if GABENCHMARK_CHECK_MODEL(ConformalModel)
    #define GABENCHMARK_N_DIMENSIONS ((GABENCHMARK_D_DIMENSIONS) + 2)
#elif GABENCHMARK_CHECK_MODEL(EuclideanModel)
    #define GABENCHMARK_N_DIMENSIONS (GABENCHMARK_D_DIMENSIONS)
#elif GABENCHMARK_CHECK_MODEL(HomogeneousModel)
    #define GABENCHMARK_N_DIMENSIONS ((GABENCHMARK_D_DIMENSIONS) + 1)
#elif GABENCHMARK_CHECK_MODEL(MinkowskiModel)
    #define GABENCHMARK_N_DIMENSIONS ((GABENCHMARK_D_DIMENSIONS) + 2)
#elif GABENCHMARK_CHECK_MODEL(SignedModel)
    #define GABENCHMARK_N_DIMENSIONS ((GABENCHMARK_P_DIMENSIONS) + (GABENCHMARK_Q_DIMENSIONS))
#else
    #error The value assumed by GABENCHMARK_MODEL is invalid.
#endif

#define GABENCHMARK_CAPTURE(FUNC, CASE) \
    BENCHMARK_CAPTURE(FUNC, CASE, "")->Unit(benchmark::kMillisecond)

#define GABENCHMARK_CAPTURE_PRODUCT(FUNC) \
    GABENCHMARK_CAPTURE(FUNC, Model=GABENCHMARK_MODEL/D=GABENCHMARK_D_DIMENSIONS/LeftGrade=GABENCHMARK_LEFT_GRADE/RightGrade=GABENCHMARK_RIGHT_GRADE/Library=GABENCHMARK_LIBRARY)

namespace gabenchmark {

    using real_t = double;

    using grade_t = std::int32_t;
    using dims_t = std::uint32_t;

    using vector_coords = std::array<real_t, GABENCHMARK_N_DIMENSIONS>;

}

#endif // __GABENCHMARK_DECLARATIONS_HPP__
