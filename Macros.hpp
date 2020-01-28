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
#define BinaryOperations           0x12
#define UnaryOperations            0x13
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

#define GABM_ITERATIONS 10000
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
    static_assert(GABM_##GROUP##_##OPERATION##_Defined, "Use GABM_DEFINE_<GROUP-NAME>[_<OPERATION-NAME>], GABM_REPORT_THAT_<OPERATION-GROUP-NAME>_[OPERATION-NAME_]IS_NOT_IMPLEMENTED, or GABM_REPORT_THAT_<OPERATION-GROUP-NAME>_[OPERATION-NAME_]LEADS_TO_COMPILATION_ERROR to define the missing operation.");

#define GABM_DEFINE_RANDOM_ARGUMENTS_FOR_OPERATION(GROUP, OPERATION, ...) \
    auto const GABM_##GROUP##_##OPERATION##_RandomArguments = gabm::WrapRandomArguments(__VA_ARGS__);

#define GABM_DEFINE_OPERATION(GROUP, OPERATION, CASE, ...) \
    constexpr static bool GABM_##GROUP##_##OPERATION##_Defined = true; \
    \
    template<typename... Types> \
    GABM_INLINE decltype(auto) GABM_##GROUP##_##OPERATION##_Impl(std::tuple<Types...> const &); \
    \
    template<typename... ExtraArgsType> \
    void GABM_##GROUP##_##OPERATION(benchmark::State &state, ExtraArgsType &&...) try { \
        std::size_t ind = 0; \
        while (state.KeepRunning()) { \
            benchmark::DoNotOptimize(GABM_##GROUP##_##OPERATION##_Impl(GABM_##GROUP##_##OPERATION##_RandomArguments[ind])); \
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
    template<typename... Types> \
    GABM_ALWAYS_INLINE decltype(auto) GABM_##GROUP##_##OPERATION##_Impl(std::tuple<Types...> const &args) { \
        auto const & [__VA_ARGS__] = args; \
        return GABM_##GROUP##_##OPERATION##_Wrapper(__VA_ARGS__); \
    }

#define GABM_REPORT_THAT_OPERATION_IS_NOT_IMPLEMENTED(GROUP, OPERATION, CASE) \
    constexpr static bool GABM_##GROUP##_##OPERATION##_Defined = true; \
    \
    template<typename... ExtraArgsType> \
    void GABM_##GROUP##_##OPERATION(benchmark::State &state, ExtraArgsType &&...) { \
        state.SkipWithError("OPERATION_NOT_IMPLEMENTED"); \
    } \
    \
    GABM_CAPTURE(GABM_##GROUP##_##OPERATION, GABM_SYSTEM_NAME, GABM_SYSTEM_VERSION, GABM_COMPILER_ID, GABM_COMPILER_VERSION, GABM_SOLUTION, GABM_MODEL, GABM_D_DIMENSIONS, CASE)

#define GABM_REPORT_THAT_OPERATION_LEADS_TO_COMPILATION_ERROR(GROUP, OPERATION, CASE) \
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

#define GABM_INITIALIZE_RANDOM_ANGLES(GLOBAL_VARIABLE) \
    class GABM_##GLOBAL_VARIABLE##_Generator { \
    public: \
        static GABM_INLINE decltype(auto) MakeRandomEntry(std::default_random_engine &random_engine) { \
            return gabm::MakeRandomAngle(random_engine); \
        } \
    }; \
    \
    gabm::RandomEntries<GABM_##GLOBAL_VARIABLE##_Generator> const GLOBAL_VARIABLE;

#define GABM_INITIALIZE_RANDOM_BLADES(GRADE, GLOBAL_VARIABLE) \
    class GABM_##GLOBAL_VARIABLE##_Generator { \
    public: \
        static GABM_INLINE decltype(auto) MakeRandomEntry(std::default_random_engine &random_engine) { \
            return gabm::MakeRandomBlade<GRADE>(random_engine); \
        } \
    }; \
    \
    gabm::RandomEntries<GABM_##GLOBAL_VARIABLE##_Generator> const GLOBAL_VARIABLE;

#define GABM_INITIALIZE_RANDOM_INVERTIBLE_BLADES(GRADE, GLOBAL_VARIABLE) \
    class GABM_##GLOBAL_VARIABLE##_Generator { \
    public: \
        static GABM_INLINE decltype(auto) MakeRandomEntry(std::default_random_engine &random_engine) { \
            return gabm::MakeRandomInvertibleBlade<GRADE>(random_engine); \
        } \
    }; \
    \
    gabm::RandomEntries<GABM_##GLOBAL_VARIABLE##_Generator> const GLOBAL_VARIABLE;

#define GABM_MAIN() \
    BENCHMARK_MAIN();

#endif // __GABM_MACROS_HPP__
