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

#ifndef __GABM_MACROS_HPP__
#define __GABM_MACROS_HPP__

#if defined(__GNUC__)
    #define GABM_INLINE inline
    #define GABM_ALWAYS_INLINE __attribute__((always_inline)) inline
#elif defined(_MSC_VER) && !defined(__clang__)
    #define GABM_INLINE inline
    #define GABM_ALWAYS_INLINE __forceinline
#else
    #define GABM_INLINE inline
    #define GABM_ALWAYS_INLINE inline
#endif

#define ConformalModel   0x01
#define EuclideanModel   0x02
#define HomogeneousModel 0x03
#define MinkowskiModel   0x04
#define GABM_CHECK_MODEL(MODEL) (MODEL == GABM_MODEL)

#define AlgorithmInverseKinematics 0x11
#define AlgorithmRayTracing        0x12
#define BinaryOperations           0x13
#define UnaryOperations            0x14
#define GABM_CHECK_OPERATION(OPERATION) (OPERATION == GABM_OPERATION)

#if GABM_CHECK_MODEL(ConformalModel)
    #define GABM_N_DIMENSIONS ((GABM_D_DIMENSIONS) + 2)
#elif GABM_CHECK_MODEL(EuclideanModel)
    #define GABM_N_DIMENSIONS (GABM_D_DIMENSIONS)
#elif GABM_CHECK_MODEL(HomogeneousModel)
    #define GABM_N_DIMENSIONS ((GABM_D_DIMENSIONS) + 1)
#elif GABM_CHECK_MODEL(MinkowskiModel)
    #define GABM_N_DIMENSIONS ((GABM_D_DIMENSIONS) + 2)
#else
    #error The value assumed by GABM_MODEL is invalid.
#endif

#define GABM_REPETITIONS 30

#define GABM_ZERO_TOLERANCE 1.0e-8

#define GABM_CAPTURE(FUNC, SYSTEM_NAME, SYSTEM_VERSION, COMPILER_ID, COMPILER_VERSION, SOLUTION, MODEL, D_DIMENSIONS, CASE) \
    BENCHMARK_CAPTURE(FUNC, SystemName:SYSTEM_NAME/SystemVersion:SYSTEM_VERSION/CompilerID:COMPILER_ID/CompilerVersion:COMPILER_VERSION/Solution:SOLUTION/Model:MODEL/D:D_DIMENSIONS/CASE, "") \
        ->Unit(benchmark::kMillisecond) \
        ->Iterations(GABM_ITERATIONS) \
        ->Repetitions(GABM_REPETITIONS) \
        ->ReportAggregatesOnly(true) \
        ->DisplayAggregatesOnly(true);

#define GABM_ASSERT_OPERATION_DEFINITION(GROUP, OPERATION) \
    static_assert(GABM_##GROUP##_##OPERATION##_Defined, "Use GABM_DEFINE_<GROUP-NAME>[_<OPERATION-NAME>], GABM_REPORT_<OPERATION-GROUP-NAME>_[OPERATION-NAME_]IS_NOT_IMPLEMENTED, or GABM_REPORT_<OPERATION-GROUP-NAME>_[OPERATION-NAME_]LEADS_TO_COMPILATION_ERROR to define the missing operation.");

#define GABM_BIND_ARGUMENTS_FOR_OPERATION(GROUP, OPERATION, ...) \
    using GABM_##GROUP##_##OPERATION##_Arguments_t = decltype(std::tie(__VA_ARGS__)); \
    GABM_##GROUP##_##OPERATION##_Arguments_t GABM_##GROUP##_##OPERATION##_Arguments = std::tie(__VA_ARGS__);

#define GABM_DEFINE_ENTRY_GENERATOR(GLOBAL_VARIABLE) \
    GABM_INLINE decltype(auto) GABM_##GLOBAL_VARIABLE##_Generator_Impl()

#define GABM_DECLARE_INPUT_ENTRIES(GLOBAL_VARIABLE) \
    class GABM_##GLOBAL_VARIABLE##_Generator { \
    public: \
        static GABM_INLINE decltype(auto) MakeEntry() { \
            return GABM_##GLOBAL_VARIABLE##_Generator_Impl(); \
        } \
    }; \
    \
    gabm::Entries<GABM_##GLOBAL_VARIABLE##_Generator> const GLOBAL_VARIABLE;

#define GABM_DECLARE_INPUT_RANDOM_ANGLES(GLOBAL_VARIABLE) \
    GABM_DEFINE_ENTRY_GENERATOR(GLOBAL_VARIABLE) { \
        return gabm::MakeRandomAngle(gabm::detail::random_engine); \
    } \
    \
    GABM_DECLARE_INPUT_ENTRIES(GLOBAL_VARIABLE)

#define GABM_DECLARE_INPUT_RANDOM_BLADES(GRADE, GLOBAL_VARIABLE) \
    GABM_DEFINE_ENTRY_GENERATOR(GLOBAL_VARIABLE) { \
        return gabm::MakeRandomBlade<GRADE>(gabm::detail::random_engine); \
    } \
    \
    GABM_DECLARE_INPUT_ENTRIES(GLOBAL_VARIABLE)

#define GABM_DECLARE_INPUT_RANDOM_INVERTIBLE_BLADES(GRADE, GLOBAL_VARIABLE) \
    GABM_DEFINE_ENTRY_GENERATOR(GLOBAL_VARIABLE) { \
        return gabm::MakeRandomInvertibleBlade<GRADE>(gabm::detail::random_engine); \
    } \
    \
    GABM_DECLARE_INPUT_ENTRIES(GLOBAL_VARIABLE)

#define GABM_DECLARE_RESULTING_ENTRIES(GLOBAL_VARIABLE) \
    class GABM_##GLOBAL_VARIABLE##_Generator { \
    public: \
        static GABM_INLINE decltype(auto) MakeEntry() { \
            return GABM_##GLOBAL_VARIABLE##_Generator_Impl(); \
        } \
    }; \
    \
    gabm::Entries<GABM_##GLOBAL_VARIABLE##_Generator> GLOBAL_VARIABLE;

#define GABM_DEFINE_OPERATION(GROUP, OPERATION, CASE, ...) \
    constexpr static bool GABM_##GROUP##_##OPERATION##_Defined = true; \
    \
    template<typename... Types, std::size_t... Indices> \
    GABM_INLINE decltype(auto) GABM_##GROUP##_##OPERATION##_Impl(std::size_t const, std::tuple<Types &...> const &, std::index_sequence<Indices...>); \
    \
    template<typename... ExtraArgsType> \
    void GABM_##GROUP##_##OPERATION(benchmark::State &state, ExtraArgsType &&...) try { \
        std::size_t ind = 0; \
        while (state.KeepRunning()) { \
            benchmark::DoNotOptimize(GABM_##GROUP##_##OPERATION##_Impl(ind, GABM_##GROUP##_##OPERATION##_Arguments, std::make_index_sequence<std::tuple_size_v<GABM_##GROUP##_##OPERATION##_Arguments_t> >())); \
            ++ind; \
        } \
    } \
    catch (std::exception &error) { \
        state.SkipWithError(("OPERATION_LEADS_TO_RUNTIME_ERROR (" + std::string(error.what()) + ")").c_str()); \
    } \
    catch (...) { \
        state.SkipWithError("OPERATION_LEADS_TO_RUNTIME_ERROR"); \
    } \
    \
    GABM_CAPTURE(GABM_##GROUP##_##OPERATION, GABM_SYSTEM_NAME, GABM_SYSTEM_VERSION, GABM_COMPILER_ID, GABM_COMPILER_VERSION, GABM_SOLUTION, GABM_MODEL, GABM_D_DIMENSIONS, CASE) \
    \
    template<typename... Types, std::size_t... Indices> \
    GABM_ALWAYS_INLINE decltype(auto) GABM_##GROUP##_##OPERATION##_Impl(std::size_t const ind, std::tuple<Types &...> const &args, std::index_sequence<Indices...>) { \
        return GABM_##GROUP##_##OPERATION##_Wrapper(std::get<Indices>(args)[ind]...); \
    }

#define GABM_REPORT_OPERATION_IS_NOT_IMPLEMENTED(GROUP, OPERATION, CASE) \
    constexpr static bool GABM_##GROUP##_##OPERATION##_Defined = true; \
    \
    template<typename... ExtraArgsType> \
    void GABM_##GROUP##_##OPERATION(benchmark::State &state, ExtraArgsType &&...) { \
        state.SkipWithError("OPERATION_NOT_IMPLEMENTED"); \
    } \
    \
    GABM_CAPTURE(GABM_##GROUP##_##OPERATION, GABM_SYSTEM_NAME, GABM_SYSTEM_VERSION, GABM_COMPILER_ID, GABM_COMPILER_VERSION, GABM_SOLUTION, GABM_MODEL, GABM_D_DIMENSIONS, CASE)

#define GABM_REPORT_OPERATION_LEADS_TO_COMPILATION_ERROR(GROUP, OPERATION, CASE) \
    constexpr static bool GABM_##GROUP##_##OPERATION##_Defined = true; \
    \
    template<typename... ExtraArgsType> \
    void GABM_##GROUP##_##OPERATION(benchmark::State &state, ExtraArgsType &&...) { \
        state.SkipWithError("OPERATION_LEADS_TO_COMPILATION_ERROR"); \
    } \
    \
    GABM_CAPTURE(GABM_##GROUP##_##OPERATION, GABM_SYSTEM_NAME, GABM_SYSTEM_VERSION, GABM_COMPILER_ID, GABM_COMPILER_VERSION, GABM_SOLUTION, GABM_MODEL, GABM_D_DIMENSIONS, CASE)

#define GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(GROUP, OPERATION, CASE) \
    constexpr static bool GABM_##GROUP##_##OPERATION##_Defined = true; \
    \
    template<typename... ExtraArgsType> \
    void GABM_##GROUP##_##OPERATION(benchmark::State &state, ExtraArgsType &&...) { \
        state.SkipWithError("MODEL_NOT_IMPLEMENTED"); \
    } \
    \
    GABM_CAPTURE(GABM_##GROUP##_##OPERATION, GABM_SYSTEM_NAME, GABM_SYSTEM_VERSION, GABM_COMPILER_ID, GABM_COMPILER_VERSION, GABM_SOLUTION, GABM_MODEL, GABM_D_DIMENSIONS, CASE)

#define GABM_MAIN() \
    int main(int argc, char **argv) { \
        benchmark::Initialize(&argc, argv); \
        if (benchmark::ReportUnrecognizedArguments(argc, argv)) { \
            return EXIT_FAILURE; \
        } \
        gabm::Initialize(); \
        benchmark::RunSpecifiedBenchmarks(); \
        return EXIT_SUCCESS; \
    }

#endif // __GABM_MACROS_HPP__
