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

/** SANITY TEST
 * 
 * When the input angles are:
 * 
 *   ang1 = deg2rad(14.0)
 *   ang2 = deg2rad(-25.0)
 *   ang3 = deg2rad(32.6)
 *   ang4 = deg2rad(66.9)
 *   ang5 = deg2rad(-42.0)
 * 
 * the result must be:
 *
 *   R1 = 0.992546 + 0.121869 * e1^e2
 *   R2 = 0.976296 + 0.210006 * e1^e3 - 0.0523604 * e2^e3 + 142.804 * e1^ni - 35.6051 * e2^ni - 43.2871 * e3^ni
 *   R3 = 0.959806 - 0.272314 * e1^e3 + 0.0678954 * e2^e3 - 404.827 * e1^ni + 100.935 * e2^ni + 161.69 * e3^ni
 *   T2 = 1 - 182.475 * e1^ni + 45.4961 * e2^ni + 41.6926 * e3^ni
 *   R4 = 0.834423 + 0.296658 * e1^e2 + 0.112228 * e1^e3 + 0.450123 * e2^e3 + 145.475 * e1^ni + 583.469 * e2^ni
 *   Rg = 0.933654 + 0.277405 * e1^e2 + 0.0937376 * e1^e3 - 0.206198 * e2^e3 + 112.644 * e1^ni - 763.223 * e2^ni - 174.171 * e3^ni
 *   Jg_f = 1351.52 * e1 - 498.052 * e2 + 2132.49 * e3 + 0.99996 * no + 3.31122e+06 * ni
 * 
 * where 'no' is the null point at the origin and 'ni' is the null point at infinity.
 */

#include "Declarations.hpp"
#include <SpecializedAlgebra.hpp>

#if !defined(GABENCHMARK_DOES_NOT_IMPLEMENT_THE_MODEL)

    #include <SpecializedUtils.hpp>
    #include <SpecializedAlgorithmInverseKinematics.hpp>
    #include "Utils.hpp"

    #if !defined(GABENCHMARK_DOES_NOT_IMPLEMENT_AlgorithmInverseKinematics)
        template<typename... ExtraArgs>
        void BM_Algorithm_InverseKinematics(benchmark::State &state, ExtraArgs &&...) {
            for (auto _ : state) {
                state.PauseTiming();
                auto ang1 = gabenchmark::MakeRandomAngle();
                auto ang2 = gabenchmark::MakeRandomAngle();
                auto ang3 = gabenchmark::MakeRandomAngle();
                auto ang4 = gabenchmark::MakeRandomAngle();
                auto ang5 = gabenchmark::MakeRandomAngle();
                state.ResumeTiming();

                benchmark::DoNotOptimize(gabenchmark::InverseKinematics(ang1, ang2, ang3, ang4, ang5));
            }
        }

        GABENCHMARK_CAPTURE_ALGORITHM(BM_Algorithm_InverseKinematics);
    #endif

#endif

BENCHMARK_MAIN();
