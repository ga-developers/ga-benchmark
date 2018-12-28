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

#include "Declarations.hpp"
#include <SpecializedAlgebra.hpp>
#include <SpecializedUtils.hpp>
#include <SpecializedProducts.hpp>
#include "Utils.hpp"

#define GABENCHMARK_CAPTURE_PRODUCT(FUNC, CASE) \
    BENCHMARK_CAPTURE(FUNC, CASE, "") \
        ->Unit(benchmark::kMillisecond);

#if defined(GABENCHMARK_IMPLEMENTS_DotProduct)
    template<typename... ExtraArgs>
    void BM_Product_DotProduct(benchmark::State &state, ExtraArgs &&...) {
        for (auto _ : state) {
            state.PauseTiming();
            auto lhs = gabenchmark::MakeRandomBlade<GABENCHMARK_LEFT_GRADE>();
            auto rhs = gabenchmark::MakeRandomBlade<GABENCHMARK_RIGHT_GRADE>();
            state.ResumeTiming();

            benchmark::DoNotOptimize(gabenchmark::DotProduct(lhs, rhs));
        }
    }

    GABENCHMARK_CAPTURE_PRODUCT(BM_Product_DotProduct, Model=GABENCHMARK_MODEL/D=GABENCHMARK_D_DIMENSIONS/LEFTGRADE=GABENCHMARK_LEFT_GRADE/RIGHTGRADE=GABENCHMARK_RIGHT_GRADE/GABENCHMARK_LIBRARY)
#endif

#if defined(GABENCHMARK_IMPLEMENTS_GeometricProduct)
    template<typename... ExtraArgs>
    void BM_Product_GeometricProduct(benchmark::State &state, ExtraArgs &&...) {
        for (auto _ : state) {
            state.PauseTiming();
            auto lhs = gabenchmark::MakeRandomBlade<GABENCHMARK_LEFT_GRADE>();
            auto rhs = gabenchmark::MakeRandomBlade<GABENCHMARK_RIGHT_GRADE>();
            state.ResumeTiming();

            benchmark::DoNotOptimize(gabenchmark::GeometricProduct(lhs, rhs));
        }
    }

    GABENCHMARK_CAPTURE_PRODUCT(BM_Product_GeometricProduct, Model=GABENCHMARK_MODEL/D=GABENCHMARK_D_DIMENSIONS/LEFTGRADE=GABENCHMARK_LEFT_GRADE/RIGHTGRADE=GABENCHMARK_RIGHT_GRADE/GABENCHMARK_LIBRARY)
#endif

#if defined(GABENCHMARK_IMPLEMENTS_HestenesInnerProduct)
    template<typename... ExtraArgs>
    void BM_Product_HestenesInnerProduct(benchmark::State &state, ExtraArgs &&...) {
        for (auto _ : state) {
            state.PauseTiming();
            auto lhs = gabenchmark::MakeRandomBlade<GABENCHMARK_LEFT_GRADE>();
            auto rhs = gabenchmark::MakeRandomBlade<GABENCHMARK_RIGHT_GRADE>();
            state.ResumeTiming();

            benchmark::DoNotOptimize(gabenchmark::HestenesInnerProduct(lhs, rhs));
        }
    }

    GABENCHMARK_CAPTURE_PRODUCT(BM_Product_HestenesInnerProduct, Model=GABENCHMARK_MODEL/D=GABENCHMARK_D_DIMENSIONS/LEFTGRADE=GABENCHMARK_LEFT_GRADE/RIGHTGRADE=GABENCHMARK_RIGHT_GRADE/GABENCHMARK_LIBRARY)
#endif

#if defined(GABENCHMARK_IMPLEMENTS_LeftContraction)
    template<typename... ExtraArgs>
    void BM_Product_LeftContraction(benchmark::State &state, ExtraArgs &&...) {
        for (auto _ : state) {
            state.PauseTiming();
            auto lhs = gabenchmark::MakeRandomBlade<GABENCHMARK_LEFT_GRADE>();
            auto rhs = gabenchmark::MakeRandomBlade<GABENCHMARK_RIGHT_GRADE>();
            state.ResumeTiming();

            benchmark::DoNotOptimize(gabenchmark::LeftContraction(lhs, rhs));
        }
    }

    GABENCHMARK_CAPTURE_PRODUCT(BM_Product_LeftContraction, Model=GABENCHMARK_MODEL/D=GABENCHMARK_D_DIMENSIONS/LEFTGRADE=GABENCHMARK_LEFT_GRADE/RIGHTGRADE=GABENCHMARK_RIGHT_GRADE/GABENCHMARK_LIBRARY)
#endif

#if defined(GABENCHMARK_IMPLEMENTS_OuterProduct)
    template<typename... ExtraArgs>
    void BM_Product_OuterProduct(benchmark::State &state, ExtraArgs &&...) {
        for (auto _ : state) {
            state.PauseTiming();
            auto lhs = gabenchmark::MakeRandomBlade<GABENCHMARK_LEFT_GRADE>();
            auto rhs = gabenchmark::MakeRandomBlade<GABENCHMARK_RIGHT_GRADE>();
            state.ResumeTiming();

            benchmark::DoNotOptimize(gabenchmark::OuterProduct(lhs, rhs));
        }
    }

    GABENCHMARK_CAPTURE_PRODUCT(BM_Product_OuterProduct, Model=GABENCHMARK_MODEL/D=GABENCHMARK_D_DIMENSIONS/LEFTGRADE=GABENCHMARK_LEFT_GRADE/RIGHTGRADE=GABENCHMARK_RIGHT_GRADE/GABENCHMARK_LIBRARY)
#endif

#if defined(GABENCHMARK_IMPLEMENTS_RegressiveProduct)
    template<typename... ExtraArgs>
    void BM_Product_RegressiveProduct(benchmark::State &state, ExtraArgs &&...) {
        for (auto _ : state) {
            state.PauseTiming();
            auto lhs = gabenchmark::MakeRandomBlade<GABENCHMARK_LEFT_GRADE>();
            auto rhs = gabenchmark::MakeRandomBlade<GABENCHMARK_RIGHT_GRADE>();
            state.ResumeTiming();

            benchmark::DoNotOptimize(gabenchmark::RegressiveProduct(lhs, rhs));
        }
    }

    GABENCHMARK_CAPTURE_PRODUCT(BM_Product_RegressiveProduct, Model=GABENCHMARK_MODEL/D=GABENCHMARK_D_DIMENSIONS/LEFTGRADE=GABENCHMARK_LEFT_GRADE/RIGHTGRADE=GABENCHMARK_RIGHT_GRADE/GABENCHMARK_LIBRARY)
#endif

#if defined(GABENCHMARK_IMPLEMENTS_RightContraction)
    template<typename... ExtraArgs>
    void BM_Product_RightContraction(benchmark::State &state, ExtraArgs &&...) {
        for (auto _ : state) {
            state.PauseTiming();
            auto lhs = gabenchmark::MakeRandomBlade<GABENCHMARK_LEFT_GRADE>();
            auto rhs = gabenchmark::MakeRandomBlade<GABENCHMARK_RIGHT_GRADE>();
            state.ResumeTiming();

            benchmark::DoNotOptimize(gabenchmark::RightContraction(lhs, rhs));
        }
    }

    GABENCHMARK_CAPTURE_PRODUCT(BM_Product_RightContraction, Model=GABENCHMARK_MODEL/D=GABENCHMARK_D_DIMENSIONS/LEFTGRADE=GABENCHMARK_LEFT_GRADE/RIGHTGRADE=GABENCHMARK_RIGHT_GRADE/GABENCHMARK_LIBRARY)
#endif

#if defined(GABENCHMARK_IMPLEMENTS_ScalarProduct)
    template<typename... ExtraArgs>
    void BM_Product_ScalarProduct(benchmark::State &state, ExtraArgs &&...) {
        for (auto _ : state) {
            state.PauseTiming();
            auto lhs = gabenchmark::MakeRandomBlade<GABENCHMARK_LEFT_GRADE>();
            auto rhs = gabenchmark::MakeRandomBlade<GABENCHMARK_RIGHT_GRADE>();
            state.ResumeTiming();

            benchmark::DoNotOptimize(gabenchmark::ScalarProduct(lhs, rhs));
        }
    }

    GABENCHMARK_CAPTURE_PRODUCT(BM_Product_ScalarProduct, Model=GABENCHMARK_MODEL/D=GABENCHMARK_D_DIMENSIONS/LEFTGRADE=GABENCHMARK_LEFT_GRADE/RIGHTGRADE=GABENCHMARK_RIGHT_GRADE/GABENCHMARK_LIBRARY)
#endif

BENCHMARK_MAIN();
