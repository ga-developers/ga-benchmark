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

    #define GABENCHMARK_DOES_NOT_IMPLEMENT_THE_MODEL

#elif GABENCHMARK_CHECK_MODEL(EuclideanModel)

    using multivector_t = framed_multi<real_t, 0, GABENCHMARK_D_DIMENSIONS>;

#elif GABENCHMARK_CHECK_MODEL(HomogeneousModel)

    using multivector_t = framed_multi<real_t, 0, GABENCHMARK_D_DIMENSIONS + 1>;

#elif GABENCHMARK_CHECK_MODEL(MinkowskiModel)

    using multivector_t = framed_multi<real_t, -1, GABENCHMARK_D_DIMENSIONS + 1>;

#endif

}

#endif // __GABENCHMARK_SPECIALIZED_ALGEBRA_HPP__
