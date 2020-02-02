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

GABM_DEFINE_UNARY_OPERATION(CliffordConjugation, arg) {
    return arg.conjugation();
}

GABM_DEFINE_UNARY_OPERATION(Dualization, arg) {
    return arg.dual();
}

GABM_DEFINE_UNARY_OPERATION(GradeInvolution, arg) {
    return arg.involution();
}

GABM_DEFINE_UNARY_OPERATION(Inversion, arg) {
    return !arg;
}

GABM_DEFINE_UNARY_OPERATION(Normalization, arg) {
    return arg.runit();
}

GABM_DEFINE_UNARY_OPERATION(Reversion, arg) {
    return ~arg;
}

GABM_DEFINE_UNARY_OPERATION(SquaredReverseNorm, arg) {
    return arg.rwt();
}

GABM_DEFINE_UNARY_OPERATION(UnaryMinus, arg) {
    return -arg;
}

GABM_REPORT_UNARY_OPERATION_IS_NOT_IMPLEMENTED(UnaryPlus)

GABM_DEFINE_UNARY_OPERATION(Undualization, arg) {
    return arg.undual();
}

#endif // __GABM_SPECIALIZED_UNARY_OPERATIONS_HPP__
