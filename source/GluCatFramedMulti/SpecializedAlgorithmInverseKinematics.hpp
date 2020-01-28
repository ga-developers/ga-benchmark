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

#ifndef __GABM_SPECIALIZED_ALGORITHM_INVERSE_KINEMATICS_HPP__
#define __GABM_SPECIALIZED_ALGORITHM_INVERSE_KINEMATICS_HPP__

template<typename Type>
inline decltype(auto) expp(Type const &arg) {
    return 1.0 + arg + arg * (0.5 * arg + arg * (arg / 6.0 + arg * arg / 24.0));
};

GABM_DEFINE_ALGORITHM_INVERSE_KINEMATICS(ang1, ang2, ang3, ang4, ang5) {
    gabm::real_t d1 = 200.0, d2 = 680.0, d3 = 150.0, d4 = 140.0, d5 = 114.2;
    gabm::real_t l12 = 890.0, l23 = 880.0;

    gabm::real_t J1_x = d1,                 J1_y = 0.0, J1_z = d2;
    gabm::real_t J2_x = d1,                 J2_y = 0.0, J2_z = d2 + l12;
    gabm::real_t J3_x = d1 + l23,           J3_y = 0.0, J3_z = d2 + l12 + d3;
    gabm::real_t Jg_x = d1 + l23 + d4 + d5, Jg_y = 0.0, Jg_z = d2 + l12 + d3;

    auto J1 = point(J1_x, J1_y, J1_z);
    auto J2 = point(J2_x, J2_y, J2_z);
    auto J3 = point(J3_x, J3_y, J3_z);
    auto Jg = point(Jg_x, Jg_y, Jg_z);

    auto Pz = point(0.0, 0.0, 1.0);
    auto Lz = dual(no ^ Pz ^ ni);
    auto R1 = expp((ang1 * 0.5) * Lz);

    auto P2_help = point(J1_x, J1_y + 1.0, J1_z);
    auto L2init = dual(J1 ^ P2_help ^ ni);
    auto L2 = apply_rotor(R1, L2init);
    auto R2 = expp((ang2 * 0.5) * L2);

    auto J2_f = apply_rotor(R2 * R1, J2);

    auto P3_help = point(J2_x, J2_y + 1.0, J2_z);
    auto L3init = dual(J2 ^ P3_help ^ ni);
    auto L3 = apply_rotor(R2 * R1, L3init);
    auto R3 = expp((ang3 * 0.5) * L3);

    auto J2_rot1 = apply_rotor(R1, J2);
    auto t2 = euclidean_vector((J2_f % e1).scalar() - (J2_rot1 % e1).scalar(), (J2_f % e2).scalar() - (J2_rot1 % e2).scalar(), (J2_f % e3).scalar() - (J2_rot1 % e3).scalar());
    auto T2 = expp(-0.5 * (t2 ^ ni));

    auto L4init = dual(J3 ^ Jg ^ ni);
    auto L4 = apply_rotor(R3 * T2 * R1, unit(L4init));
    auto R4 = expp((ang4 * 0.5) * L4);

    auto Pg_help = point(J3_x, J3_y + 1.0, J3_z);
    auto Lginit = dual(J3 ^ Pg_help ^ ni);
    auto Lg = apply_rotor(R4 * R3 * T2 * R1, Lginit);
    auto Rg = expp((ang5 * 0.5) * Lg);

    auto Jg_f = apply_rotor(Rg * R3 * T2 * R1, Jg);

    return std::make_tuple(R1, R2, R3, T2, R4, Rg, Jg_f);
}

#endif // __GABM_SPECIALIZED_ALGORITHM_INVERSE_KINEMATICS_HPP__
