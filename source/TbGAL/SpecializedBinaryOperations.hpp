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

GABM_REPORT_THAT_BINARY_OPERATION_IS_NOT_IMPLEMENTED(Addition)

GABM_REPORT_THAT_BINARY_OPERATION_IS_NOT_IMPLEMENTED(CommutatorProduct)

GABM_DEFINE_BINARY_OPERATION(DotProduct, lhs, rhs) {
    return dot(lhs, rhs);
}

GABM_DEFINE_BINARY_OPERATION(GeometricProduct, lhs, rhs) {
    return gp(lhs, rhs);
}

GABM_DEFINE_BINARY_OPERATION(HestenesInnerProduct, lhs, rhs) {
    return hip(lhs, rhs);
}

GABM_DEFINE_BINARY_OPERATION(InverseGeometricProduct, lhs, rhs) {
    return igp(lhs, rhs);
}

GABM_DEFINE_BINARY_OPERATION(LeftContraction, lhs, rhs) {
    return lcont(lhs, rhs);
}

GABM_DEFINE_BINARY_OPERATION(OuterProduct, lhs, rhs) {
    return op(lhs, rhs);
}

GABM_REPORT_THAT_BINARY_OPERATION_IS_NOT_IMPLEMENTED(RegressiveProduct)

GABM_DEFINE_BINARY_OPERATION(RightContraction, lhs, rhs) {
    return rcont(lhs, rhs);
}

GABM_DEFINE_BINARY_OPERATION(ScalarProduct, lhs, rhs) {
    return sp(lhs, rhs);
}

GABM_REPORT_THAT_BINARY_OPERATION_IS_NOT_IMPLEMENTED(Subtraction)

#endif // __GABM_SPECIALIZED_BINARY_OPERATIONS_HPP__
