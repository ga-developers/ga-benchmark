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

/* SANITY TEST
 * 
 * When the input angles are:
 * 
 *   ang1 = deg2rad(14.0)
 *   ang2 = deg2rad(-25.0)
 *   ang3 = deg2rad(32.6)
 *   ang4 = deg2rad(66.9)
 *   ang5 = deg2rad(-42.0)
 * 
 * the result must be:
 *
 *   R1 = 0.992546 + 0.121869 * e1^e2
 *   R2 = 0.976296 + 0.210006 * e1^e3 - 0.0523604 * e2^e3 + 142.804 * e1^ni - 35.6051 * e2^ni - 43.2871 * e3^ni
 *   R3 = 0.959806 - 0.272314 * e1^e3 + 0.0678954 * e2^e3 - 404.827 * e1^ni + 100.935 * e2^ni + 161.69 * e3^ni
 *   T2 = 1 - 182.475 * e1^ni + 45.4961 * e2^ni + 41.6926 * e3^ni
 *   R4 = 0.834423 + 0.296658 * e1^e2 + 0.112228 * e1^e3 + 0.450123 * e2^e3 + 145.475 * e1^ni + 583.469 * e2^ni
 *   Rg = 0.933654 + 0.277405 * e1^e2 + 0.0937376 * e1^e3 - 0.206198 * e2^e3 + 112.644 * e1^ni - 763.223 * e2^ni - 174.171 * e3^ni
 *   Jg_f = 1351.52 * e1 - 498.052 * e2 + 2132.49 * e3 + 0.99996 * no + 3.31122e+06 * ni
 * 
 * where 'no' is the null point at the origin and 'ni' is the null point at infinity.
 */

#define GABM_ITERATIONS 10000

#include "Macros.hpp"
#include "Types.hpp"
#include <SpecializedAlgebra.hpp>

#if !defined(GABM_MODEL_NOT_IMPLEMENTED)

    #include "Utils.hpp"

    #define GABM_DEFINE_ALGORITHM_INVERSE_KINEMATICS(ANG1_ARG, ANG2_ARG, ANG3_ARG, ANG4_ARG, ANG5_ARG) \
        GABM_DECLARE_INPUT_RANDOM_ANGLES(random_angles1) \
        GABM_DECLARE_INPUT_RANDOM_ANGLES(random_angles2) \
        GABM_DECLARE_INPUT_RANDOM_ANGLES(random_angles3) \
        GABM_DECLARE_INPUT_RANDOM_ANGLES(random_angles4) \
        GABM_DECLARE_INPUT_RANDOM_ANGLES(random_angles5) \
        \
        GABM_BIND_ARGUMENTS_FOR_OPERATION(Algorithm, InverseKinematics, random_angles1, random_angles2, random_angles3, random_angles4, random_angles5) \
        \
        GABM_INLINE decltype(auto) GABM_Algorithm_InverseKinematics_Wrapper(gabm::real_t, gabm::real_t, gabm::real_t, gabm::real_t, gabm::real_t); \
        \
        GABM_DEFINE_OPERATION(Algorithm, InverseKinematics, _:_, ANG1_ARG, ANG2_ARG, ANG3_ARG, ANG4_ARG, ANG5_ARG) \
        \
        GABM_ALWAYS_INLINE decltype(auto) GABM_Algorithm_InverseKinematics_Wrapper(gabm::real_t ANG1_ARG, gabm::real_t ANG2_ARG, gabm::real_t ANG3_ARG, gabm::real_t ANG4_ARG, gabm::real_t ANG5_ARG)

    #define GABM_REPORT_ALGORITHM_INVERSE_KINEMATICS_IS_NOT_IMPLEMENTED() \
        GABM_REPORT_OPERATION_IS_NOT_IMPLEMENTED(Algorithm, InverseKinematics, _:_)
    
    #define GABM_REPORT_ALGORITHM_INVERSE_KINEMATICS_LEADS_TO_COMPILATION_ERROR() \
        GABM_REPORT_OPERATION_LEADS_TO_COMPILATION_ERROR(Algorithm, InverseKinematics, _:_)

    #include <SpecializedAlgorithmInverseKinematics.hpp>

#else

    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(Algorithm, InverseKinematics, _:_)

#endif

GABM_ASSERT_OPERATION_DEFINITION(Algorithm, InverseKinematics)

GABM_MAIN()
