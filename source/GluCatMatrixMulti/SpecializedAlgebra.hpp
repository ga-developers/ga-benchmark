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
along with GA-Benchmark. If not, see <https://www.gnu.org/licenses/>.
/**/

#ifndef __GABENCHMARK_SPECIALIZED_ALGEBRA_HPP__
#define __GABENCHMARK_SPECIALIZED_ALGEBRA_HPP__

#include <glucat/glucat.h>

typedef glucat::tuning<
    glucat::DEFAULT_Mult_Matrix_Threshold,
    glucat::DEFAULT_Div_Max_Steps,
    glucat::DEFAULT_Sqrt_Max_Steps,
    glucat::DEFAULT_Log_Max_Outer_Steps,
    glucat::DEFAULT_Log_Max_Inner_Steps,
    glucat::DEFAULT_Basis_Max_Count,
    glucat::DEFAULT_Fast_Size_Threshold,
    glucat::DEFAULT_Inv_Fast_Dim_Threshold,
    glucat::DEFAULT_Products_Size_Threshold,
    glucat::precision_promoted
> Tune_P;

#include <glucat/glucat_imp.h>

namespace gabenchmark {

    using namespace glucat;

#if GABENCHMARK_CHECK_MODEL(ConformalModel)

    // GluCat requires mapping from Minkoski to Conformal and vice-versa.

    #if GABENCHMARK_CHECK_OPERATION(Products)

        // For products, only native implementations of the model are considered.
        #define GABENCHMARK_DOES_NOT_IMPLEMENT_THE_MODEL

        #define GABENCHMARK_GLUCAT_NEGATIVE_GENERATORS 0
        #define GABENCHMARK_GLUCAT_POSITIVE_GENERATORS 0

    #else

        #define GABENCHMARK_GLUCAT_NEGATIVE_GENERATORS 1
        #define GABENCHMARK_GLUCAT_POSITIVE_GENERATORS ((GABENCHMARK_D_DIMENSIONS) + 1)

    #endif

#elif GABENCHMARK_CHECK_MODEL(EuclideanModel)

    #define GABENCHMARK_GLUCAT_NEGATIVE_GENERATORS 0
    #define GABENCHMARK_GLUCAT_POSITIVE_GENERATORS (GABENCHMARK_D_DIMENSIONS)

#elif GABENCHMARK_CHECK_MODEL(HomogeneousModel)

    #define GABENCHMARK_GLUCAT_NEGATIVE_GENERATORS 0
    #define GABENCHMARK_GLUCAT_POSITIVE_GENERATORS ((GABENCHMARK_D_DIMENSIONS) + 1)

#elif GABENCHMARK_CHECK_MODEL(MinkowskiModel)

    #define GABENCHMARK_GLUCAT_NEGATIVE_GENERATORS 1
    #define GABENCHMARK_GLUCAT_POSITIVE_GENERATORS ((GABENCHMARK_D_DIMENSIONS) + 1)

#endif

    using multivector_t = matrix_multi<real_t, -std::max(GABENCHMARK_GLUCAT_NEGATIVE_GENERATORS, GABENCHMARK_GLUCAT_POSITIVE_GENERATORS), std::max(GABENCHMARK_GLUCAT_NEGATIVE_GENERATORS, GABENCHMARK_GLUCAT_POSITIVE_GENERATORS)>;

}

#endif // __GABENCHMARK_SPECIALIZED_ALGEBRA_HPP__
