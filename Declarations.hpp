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
#include <random>
#include <vector>

#include <benchmark/benchmark.h>

#define Euclidean   0x01
#define Conformal   0x02
#define Homogeneous 0x03
#define Minkowski   0x04
#define Signed      0x05
#define GABENCHMARK_CHECK_MODEL(MODEL) (MODEL == GABENCHMARK_MODEL)

#define Products    0x11
#define GABENCHMARK_CHECK_OPERATION(OPERATION) (OPERATION == GABENCHMARK_OPERATION)

#if GABENCHMARK_CHECK_MODEL(Euclidean)
    #define GABENCHMARK_N_DIMENSIONS (GABENCHMARK_D_DIMENSIONS)
#elif GABENCHMARK_CHECK_MODEL(Conformal)
    #define GABENCHMARK_N_DIMENSIONS ((GABENCHMARK_D_DIMENSIONS) + 2)
#elif GABENCHMARK_CHECK_MODEL(Homogeneous)
    #define GABENCHMARK_N_DIMENSIONS ((GABENCHMARK_D_DIMENSIONS) + 1)
#elif GABENCHMARK_CHECK_MODEL(Minkowski)
    #define GABENCHMARK_N_DIMENSIONS ((GABENCHMARK_D_DIMENSIONS) + 2)
#elif GABENCHMARK_CHECK_MODEL(Signed)
    #define GABENCHMARK_N_DIMENSIONS ((GABENCHMARK_P_DIMENSIONS) + (GABENCHMARK_Q_DIMENSIONS))
#else
    #error The value assumed by GABENCHMARK_MODEL is invalid.
#endif

namespace gabenchmark {

    using real_t = double;

    using grade_t = std::int32_t;
    using dims_t = std::uint32_t;

    using vector_coords = std::array<real_t, GABENCHMARK_N_DIMENSIONS>;

}

#endif // __GABENCHMARK_DECLARATIONS_HPP__
