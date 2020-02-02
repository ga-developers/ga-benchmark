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

#ifndef __GABM_SPECIALIZED_UNARY_OPERATIONS_HPP__
#define __GABM_SPECIALIZED_UNARY_OPERATIONS_HPP__

GABM_REPORT_UNARY_OPERATION_IS_NOT_IMPLEMENTED(CliffordConjugation)

GABM_REPORT_UNARY_OPERATION_IS_NOT_IMPLEMENTED(Dualization)

GABM_REPORT_UNARY_OPERATION_IS_NOT_IMPLEMENTED(GradeInvolution)

GABM_DEFINE_UNARY_OPERATION(Inversion, arg) {
    return eval(!arg);
}

GABM_REPORT_UNARY_OPERATION_IS_NOT_IMPLEMENTED(Normalization)

GABM_DEFINE_UNARY_OPERATION(Reversion, arg) {
    return eval(~arg);
}

GABM_REPORT_UNARY_OPERATION_IS_NOT_IMPLEMENTED(SquaredReverseNorm)

GABM_REPORT_UNARY_OPERATION_IS_NOT_IMPLEMENTED(UnaryMinus)

GABM_REPORT_UNARY_OPERATION_IS_NOT_IMPLEMENTED(UnaryPlus)

GABM_REPORT_UNARY_OPERATION_IS_NOT_IMPLEMENTED(Undualization)

#endif // __GABM_SPECIALIZED_UNARY_OPERATIONS_HPP__
