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
