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
    return arg + arg * ((arg * 0.5) + arg * ((arg / 6.0) + arg * (arg / 24.0))) + 1.0;
};

GABM_DEFINE_ALGORITHM_INVERSE_KINEMATICS(ang1, ang2, ang3, ang4, ang5) {
    gabm::real_t d1 = 200.0, d2 = 680.0, d3 = 150.0, d4 = 140.0, d5 = 114.2;
    gabm::real_t l12 = 890.0, l23 = 880.0;

    gabm::real_t J1_x = d1,                 J1_y = 0.0, J1_z = d2;
    gabm::real_t J2_x = d1,                 J2_y = 0.0, J2_z = d2 + l12;
    gabm::real_t J3_x = d1 + l23,           J3_y = 0.0, J3_z = d2 + l12 + d3;
    gabm::real_t Jg_x = d1 + l23 + d4 + d5, Jg_y = 0.0, Jg_z = d2 + l12 + d3;

    auto J1 = cga::Construct::point(J1_x, J1_y, J1_z);
    auto J2 = cga::Construct::point(J2_x, J2_y, J2_z);
    auto J3 = cga::Construct::point(J3_x, J3_y, J3_z);
    auto Jg = cga::Construct::point(Jg_x, Jg_y, Jg_z);

    auto Pz = cga::Construct::point(0.0, 0.0, 1.0);
    auto Lz = (no ^ Pz ^ ni).dual();
    auto R1 = expp(Lz * (0.5 * ang1));

    auto P2_help = cga::Construct::point(J1_x, J1_y + 1.0, J1_z);
    auto L2init = (J1 ^ P2_help ^ ni).dual();
    auto L2 = L2init.spin(R1);
    auto R2 = expp(L2 * (0.5 * ang2)); 

    auto J2_f = J2.spin(R2 * R1);

    auto P3_help = cga::Construct::point(J2_x, J2_y + 1.0, J2_z);
    auto L3init = (J2 ^ P3_help ^ ni).dual();
    auto L3 = L3init.spin(R2 * R1);
    auto R3 = expp(L3 * (0.5 * ang3));

    auto J2_rot1 = J2.spin(R1);
    auto t2 = vector_t((e1 <= J2_f)[0] - (e1 <= J2_rot1)[0], (e2 <= J2_f)[0] - (e2 <= J2_rot1)[0], (e3 <= J2_f)[0] - (e3 <= J2_rot1)[0]);
    auto T2 = expp((t2 ^ ni) * (-0.5));

    auto L4init = (J3 ^ Jg ^ ni).dual();
    auto L4 = L4init.runit().spin(R3 * T2 * R1);
    auto R4 = expp(L4 * (0.5 * ang4));

    auto Pg_help = cga::Construct::point(J3_x, J3_y + 1.0, J3_z);
    auto Lginit = (J3 ^ Pg_help ^ ni).dual();
    auto Lg = Lginit.spin(R4 * R3 * T2 * R1);
    auto Rg = expp(Lg * (0.5 * ang5));

    auto Jg_f = Jg.spin(Rg * R3 * T2 * R1);

    return std::make_tuple(R1, R2, R3, T2, R4, Rg, Jg_f);
}

#endif // __GABM_SPECIALIZED_ALGORITHM_INVERSE_KINEMATICS_HPP__
