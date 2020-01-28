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

#include "Macros.hpp"
#include "Types.hpp"
#include <SpecializedAlgebra.hpp>

#if !defined(GABM_MODEL_NOT_IMPLEMENTED)

    #include "Utils.hpp"

    #define GABM_DEFINE_UNARY_OPERATION(OPERATION, ARG) \
        template<typename ArgumentType> \
        GABM_INLINE decltype(auto) GABM_UnaryOperation_##OPERATION##_Wrapper(ArgumentType const &); \
        \
        GABM_DEFINE_OPERATION(UnaryOperation, OPERATION, Grade:GABM_GRADE, ARG) \
        \
        template<typename ArgumentType> \
        GABM_ALWAYS_INLINE decltype(auto) GABM_UnaryOperation_##OPERATION##_Wrapper(ArgumentType const &ARG)

    #define GABM_REPORT_THAT_UNARY_OPERATION_IS_NOT_IMPLEMENTED(OPERATION) \
        GABM_REPORT_THAT_OPERATION_IS_NOT_IMPLEMENTED(UnaryOperation, OPERATION, Grade:GABM_GRADE)
    
    #define GABM_REPORT_THAT_UNARY_OPERATION_LEADS_TO_COMPILATION_ERROR(OPERATION) \
        GABM_REPORT_THAT_OPERATION_LEADS_TO_COMPILATION_ERROR(UnaryOperation, OPERATION, Grade:GABM_GRADE)

    GABM_INITIALIZE_RANDOM_BLADES(GABM_GRADE, random_blades)
    GABM_INITIALIZE_RANDOM_INVERTIBLE_BLADES(GABM_GRADE, random_invertible_blades)

    GABM_DEFINE_RANDOM_ARGUMENTS_FOR_OPERATION(UnaryOperation, CliffordConjugation, random_blades)
    GABM_DEFINE_RANDOM_ARGUMENTS_FOR_OPERATION(UnaryOperation, Dualization, random_blades)
    GABM_DEFINE_RANDOM_ARGUMENTS_FOR_OPERATION(UnaryOperation, GradeInvolution, random_blades)
    GABM_DEFINE_RANDOM_ARGUMENTS_FOR_OPERATION(UnaryOperation, Inversion, random_invertible_blades)
    GABM_DEFINE_RANDOM_ARGUMENTS_FOR_OPERATION(UnaryOperation, Normalization, random_invertible_blades)
    GABM_DEFINE_RANDOM_ARGUMENTS_FOR_OPERATION(UnaryOperation, Reversion, random_blades)
    GABM_DEFINE_RANDOM_ARGUMENTS_FOR_OPERATION(UnaryOperation, SquaredReverseNorm, random_blades)
    GABM_DEFINE_RANDOM_ARGUMENTS_FOR_OPERATION(UnaryOperation, UnaryMinus, random_blades)
    GABM_DEFINE_RANDOM_ARGUMENTS_FOR_OPERATION(UnaryOperation, UnaryPlus, random_blades)
    GABM_DEFINE_RANDOM_ARGUMENTS_FOR_OPERATION(UnaryOperation, Undualization, random_blades)

    #include <SpecializedUnaryOperations.hpp>

#else

    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(UnaryOperation, CliffordConjugation, Grade:GABM_GRADE)
    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(UnaryOperation, Dualization, Grade:GABM_GRADE)
    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(UnaryOperation, GradeInvolution, Grade:GABM_GRADE)
    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(UnaryOperation, Inversion, Grade:GABM_GRADE)
    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(UnaryOperation, Normalization, Grade:GABM_GRADE)
    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(UnaryOperation, Reversion, Grade:GABM_GRADE)
    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(UnaryOperation, SquaredReverseNorm, Grade:GABM_GRADE)
    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(UnaryOperation, UnaryMinus, Grade:GABM_GRADE)
    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(UnaryOperation, UnaryPlus, Grade:GABM_GRADE)
    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(UnaryOperation, Undualization, Grade:GABM_GRADE)

#endif

GABM_ASSERT_OPERATION_DEFINITION(UnaryOperation, CliffordConjugation)
GABM_ASSERT_OPERATION_DEFINITION(UnaryOperation, Dualization)
GABM_ASSERT_OPERATION_DEFINITION(UnaryOperation, GradeInvolution)
GABM_ASSERT_OPERATION_DEFINITION(UnaryOperation, Inversion)
GABM_ASSERT_OPERATION_DEFINITION(UnaryOperation, Normalization)
GABM_ASSERT_OPERATION_DEFINITION(UnaryOperation, Reversion)
GABM_ASSERT_OPERATION_DEFINITION(UnaryOperation, SquaredReverseNorm)
GABM_ASSERT_OPERATION_DEFINITION(UnaryOperation, UnaryMinus)
GABM_ASSERT_OPERATION_DEFINITION(UnaryOperation, UnaryPlus)
GABM_ASSERT_OPERATION_DEFINITION(UnaryOperation, Undualization)

GABM_MAIN();
