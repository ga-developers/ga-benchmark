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

#ifndef __GABM_SPECIALIZED_BINARY_OPERATIONS_HPP__
#define __GABM_SPECIALIZED_BINARY_OPERATIONS_HPP__

GABM_DEFINE_BINARY_OPERATION(Addition, lhs, rhs) {
    return eval(lhs + rhs);
}

GABM_REPORT_THAT_BINARY_OPERATION_IS_NOT_IMPLEMENTED(CommutatorProduct)

GABM_REPORT_THAT_BINARY_OPERATION_IS_NOT_IMPLEMENTED(DotProduct)

GABM_DEFINE_BINARY_OPERATION(GeometricProduct, lhs, rhs) {
    return eval(lhs * rhs);
}

#if (GABM_LEFT_GRADE) != 0 && (GABM_RIGHT_GRADE) != 0
    GABM_DEFINE_BINARY_OPERATION(HestenesInnerProduct, lhs, rhs) {
        return eval(lhs & rhs);
    }
#else
    GABM_REPORT_THAT_BINARY_OPERATION_LEADS_TO_COMPILATION_ERROR(HestenesInnerProduct)
#endif

GABM_REPORT_THAT_BINARY_OPERATION_IS_NOT_IMPLEMENTED(InverseGeometricProduct)

GABM_REPORT_THAT_BINARY_OPERATION_IS_NOT_IMPLEMENTED(LeftContraction)

#if ((GABM_LEFT_GRADE) + (GABM_RIGHT_GRADE)) <= (GABM_N_DIMENSIONS)
    GABM_DEFINE_BINARY_OPERATION(OuterProduct, lhs, rhs) {
        return eval(lhs ^ rhs);
    }
#else
    GABM_REPORT_THAT_BINARY_OPERATION_LEADS_TO_COMPILATION_ERROR(OuterProduct)
#endif

GABM_REPORT_THAT_BINARY_OPERATION_IS_NOT_IMPLEMENTED(RegressiveProduct)

GABM_REPORT_THAT_BINARY_OPERATION_IS_NOT_IMPLEMENTED(RightContraction)

#if (GABM_LEFT_GRADE) == (GABM_RIGHT_GRADE)
    GABM_DEFINE_BINARY_OPERATION(ScalarProduct, lhs, rhs) {
        return eval(scalar(lhs, rhs));
    }
#else
    GABM_REPORT_THAT_BINARY_OPERATION_LEADS_TO_COMPILATION_ERROR(ScalarProduct)
#endif

GABM_DEFINE_BINARY_OPERATION(Subtraction, lhs, rhs) {
    return eval(lhs - rhs);
}

#endif // __GABM_SPECIALIZED_BINARY_OPERATIONS_HPP__
