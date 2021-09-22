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

#define GABM_ITERATIONS 10000

#include "Macros.hpp"
#include "Types.hpp"
#include <SpecializedAlgebra.hpp>

#if !defined(GABM_MODEL_NOT_IMPLEMENTED)

    #include "Utils.hpp"

    #define GABM_DEFINE_BINARY_OPERATION(OPERATION, LHS_ARG, RHS_ARG) \
        template<typename LeftArgumentType, typename RightArgumentType> \
        GABM_INLINE decltype(auto) GABM_BinaryOperation_##OPERATION##_Wrapper(LeftArgumentType const &, RightArgumentType const &); \
        \
        GABM_DEFINE_OPERATION(BinaryOperation, OPERATION, LeftGrade:GABM_LEFT_GRADE/RightGrade:GABM_RIGHT_GRADE, LHS_ARG, RHS_ARG) \
        \
        template<typename LeftArgumentType, typename RightArgumentType> \
        GABM_ALWAYS_INLINE decltype(auto) GABM_BinaryOperation_##OPERATION##_Wrapper(LeftArgumentType const &LHS_ARG, RightArgumentType const &RHS_ARG)

    #define GABM_REPORT_BINARY_OPERATION_IS_NOT_IMPLEMENTED(OPERATION) \
        GABM_REPORT_OPERATION_IS_NOT_IMPLEMENTED(BinaryOperation, OPERATION, LeftGrade:GABM_LEFT_GRADE/RightGrade:GABM_RIGHT_GRADE)
    
    #define GABM_REPORT_BINARY_OPERATION_LEADS_TO_COMPILATION_ERROR(OPERATION) \
        GABM_REPORT_OPERATION_LEADS_TO_COMPILATION_ERROR(BinaryOperation, OPERATION, LeftGrade:GABM_LEFT_GRADE/RightGrade:GABM_RIGHT_GRADE)

    GABM_DECLARE_INPUT_RANDOM_BLADES(GABM_LEFT_GRADE, left_random_blades)
    GABM_DECLARE_INPUT_RANDOM_BLADES(GABM_RIGHT_GRADE, right_random_blades)
    GABM_DECLARE_INPUT_RANDOM_INVERTIBLE_BLADES(GABM_RIGHT_GRADE, right_random_invertible_blades)

    GABM_BIND_ARGUMENTS_FOR_OPERATION(BinaryOperation, Addition, left_random_blades, right_random_blades)
    GABM_BIND_ARGUMENTS_FOR_OPERATION(BinaryOperation, CommutatorProduct, left_random_blades, right_random_blades)
    GABM_BIND_ARGUMENTS_FOR_OPERATION(BinaryOperation, DotProduct, left_random_blades, right_random_blades)
    GABM_BIND_ARGUMENTS_FOR_OPERATION(BinaryOperation, GeometricProduct, left_random_blades, right_random_blades)
    GABM_BIND_ARGUMENTS_FOR_OPERATION(BinaryOperation, HestenesInnerProduct, left_random_blades, right_random_blades)
    GABM_BIND_ARGUMENTS_FOR_OPERATION(BinaryOperation, InverseGeometricProduct, left_random_blades, right_random_invertible_blades)
    GABM_BIND_ARGUMENTS_FOR_OPERATION(BinaryOperation, LeftContraction, left_random_blades, right_random_blades)
    GABM_BIND_ARGUMENTS_FOR_OPERATION(BinaryOperation, OuterProduct, left_random_blades, right_random_blades)
    GABM_BIND_ARGUMENTS_FOR_OPERATION(BinaryOperation, RegressiveProduct, left_random_blades, right_random_blades)
    GABM_BIND_ARGUMENTS_FOR_OPERATION(BinaryOperation, RightContraction, left_random_blades, right_random_blades)
    GABM_BIND_ARGUMENTS_FOR_OPERATION(BinaryOperation, ScalarProduct, left_random_blades, right_random_blades)
    GABM_BIND_ARGUMENTS_FOR_OPERATION(BinaryOperation, Subtraction, left_random_blades, right_random_blades)

    #include <SpecializedBinaryOperations.hpp>

#else

    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(BinaryOperation, Addition, LeftGrade:GABM_LEFT_GRADE/RightGrade:GABM_RIGHT_GRADE)
    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(BinaryOperation, CommutatorProduct, LeftGrade:GABM_LEFT_GRADE/RightGrade:GABM_RIGHT_GRADE)
    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(BinaryOperation, DotProduct, LeftGrade:GABM_LEFT_GRADE/RightGrade:GABM_RIGHT_GRADE)
    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(BinaryOperation, GeometricProduct, LeftGrade:GABM_LEFT_GRADE/RightGrade:GABM_RIGHT_GRADE)
    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(BinaryOperation, HestenesInnerProduct, LeftGrade:GABM_LEFT_GRADE/RightGrade:GABM_RIGHT_GRADE)
    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(BinaryOperation, InverseGeometricProduct, LeftGrade:GABM_LEFT_GRADE/RightGrade:GABM_RIGHT_GRADE)
    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(BinaryOperation, LeftContraction, LeftGrade:GABM_LEFT_GRADE/RightGrade:GABM_RIGHT_GRADE)
    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(BinaryOperation, OuterProduct, LeftGrade:GABM_LEFT_GRADE/RightGrade:GABM_RIGHT_GRADE)
    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(BinaryOperation, RegressiveProduct, LeftGrade:GABM_LEFT_GRADE/RightGrade:GABM_RIGHT_GRADE)
    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(BinaryOperation, RightContraction, LeftGrade:GABM_LEFT_GRADE/RightGrade:GABM_RIGHT_GRADE)
    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(BinaryOperation, ScalarProduct, LeftGrade:GABM_LEFT_GRADE/RightGrade:GABM_RIGHT_GRADE)
    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(BinaryOperation, Subtraction, LeftGrade:GABM_LEFT_GRADE/RightGrade:GABM_RIGHT_GRADE)

#endif

GABM_ASSERT_OPERATION_DEFINITION(BinaryOperation, Addition)
GABM_ASSERT_OPERATION_DEFINITION(BinaryOperation, CommutatorProduct)
GABM_ASSERT_OPERATION_DEFINITION(BinaryOperation, DotProduct)
GABM_ASSERT_OPERATION_DEFINITION(BinaryOperation, GeometricProduct)
GABM_ASSERT_OPERATION_DEFINITION(BinaryOperation, HestenesInnerProduct)
GABM_ASSERT_OPERATION_DEFINITION(BinaryOperation, InverseGeometricProduct)
GABM_ASSERT_OPERATION_DEFINITION(BinaryOperation, LeftContraction)
GABM_ASSERT_OPERATION_DEFINITION(BinaryOperation, OuterProduct)
GABM_ASSERT_OPERATION_DEFINITION(BinaryOperation, RegressiveProduct)
GABM_ASSERT_OPERATION_DEFINITION(BinaryOperation, RightContraction)
GABM_ASSERT_OPERATION_DEFINITION(BinaryOperation, ScalarProduct)
GABM_ASSERT_OPERATION_DEFINITION(BinaryOperation, Subtraction)

GABM_MAIN()
