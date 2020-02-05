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
    return conjugate(arg);
}

GABM_DEFINE_UNARY_OPERATION(Dualization, arg) {
    return dual(arg);
}

GABM_DEFINE_UNARY_OPERATION(GradeInvolution, arg) {
    return involute(arg);
}

GABM_DEFINE_UNARY_OPERATION(Inversion, arg) {
    return inv(arg);
}

GABM_DEFINE_UNARY_OPERATION(Normalization, arg) {
    return unit(arg);
}

GABM_DEFINE_UNARY_OPERATION(Reversion, arg) {
    return reverse(arg);
}

GABM_DEFINE_UNARY_OPERATION(SquaredReverseNorm, arg) {
    return rnorm_sqr(arg);
}

GABM_DEFINE_UNARY_OPERATION(UnaryMinus, arg) {
    return -arg;
}

GABM_DEFINE_UNARY_OPERATION(UnaryPlus, arg) {
    return +arg;
}

GABM_DEFINE_UNARY_OPERATION(Undualization, arg) {
    return undual(arg);
}

#endif // __GABM_SPECIALIZED_UNARY_OPERATIONS_HPP__
