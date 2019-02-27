/**
Copyright(C) 2018 ga-developers

Repository: https://github.com/ga-developers/ga-benchmark.git

This file is part of the GA-Benchmark project.

GA-Benchmark is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

GA-Benchmark is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GA-Benchmark. If not, see <https://www.gnu.org/licenses/>.
/**/

#ifndef __GABENCHMARK_SPECIALIZED_ALGORITHM_INVERSE_KINEMATICS_HPP__
#define __GABENCHMARK_SPECIALIZED_ALGORITHM_INVERSE_KINEMATICS_HPP__

namespace gabenchmark {

    template<typename Type>
    decltype(auto) expp(Type const &arg) {
        auto lazy = make_lazy_context(arg);
        auto x = lazy.template argument<0>();
        return lazy.eval(c<1> + x + x * x / c<2> + x * x * x / c<6> + x * x * x * x / c<24>);
    };

    template<typename Scalar>
    constexpr decltype(auto) InverseKinematics(Scalar const &ang1, Scalar const &ang2, Scalar const &ang3, Scalar const &ang4, Scalar const &ang5) {
        auto d1 = c<200>; auto d2 = c<680>; auto d3 = c<150>; auto d4 = c<140>; auto d5 = c<1142> / c<10>;
        auto l12 = c<890>; auto l23 = c<880>;

        auto J1_x = d1;                 auto J1_y = c<0>; auto J1_z = d2;
        auto J2_x = d1;                 auto J2_y = c<0>; auto J2_z = d2 + l12;
        auto J3_x = d1 + l23;           auto J3_y = c<0>; auto J3_z = d2 + l12 + d3;
        auto Jg_x = d1 + l23 + d4 + d5; auto Jg_y = c<0>; auto Jg_z = d2 + l12 + d3;

        auto J1 = point(J1_x, J1_y, J1_z);
        auto J2 = point(J2_x, J2_y, J2_z);
        auto J3 = point(J3_x, J3_y, J3_z);
        auto Jg = point(Jg_x, Jg_y, Jg_z);

        auto Pz = point(c<0>, c<0>, c<1>);
        auto Lz = dual(no ^ Pz ^ ni);
        auto R1 = expp((ang1 / c<2>) * Lz);

        auto P2_help = point(J1_x, J1_y + c<1>, J1_z);
        auto L2init = dual(J1 ^ P2_help ^ ni);
        auto L2 = apply_rotor(R1, L2init);
        auto R2 = expp((ang2 / c<2>) * L2); 

        auto J2_f = apply_rotor(R2 * R1, J2);

        auto P3_help = point(J2_x, J2_y + c<1>, J2_z);
        auto L3init = dual(J2 ^ P3_help ^ ni);
        auto L3 = apply_rotor(R2 * R1, L3init);
        auto R3 = expp((ang3 / c<2>) * L3);

        auto J2_rot1 = apply_rotor(R1, J2);
        auto t2 = (sp(J2_f, e1) - sp(J2_rot1, e1)) * e1 + (sp(J2_f, e2) - sp(J2_rot1, e2)) * e2 + (sp(J2_f, e3) - sp(J2_rot1, e3)) * e3;
        auto T2 = expp((c<-1> / c<2>) * (t2 ^ ni));

        auto L4init = dual(J3 ^ Jg ^ ni);
        auto L4 = apply_rotor(R3 * T2 * R1, L4init / rnorm(L4init));
        auto R4 = expp((ang4 / c<2>) * L4);

        auto Pg_help = point(J3_x, J3_y + c<1>, J3_z);
        auto Lginit = dual(J3 ^ Pg_help ^ ni);
        auto Lg = apply_rotor(R4 * R3 * T2 * R1, Lginit);
        auto Rg = expp((ang5 / c<2>) * Lg);

        auto Jg_f = apply_rotor(Rg * R3 * T2 * R1, Jg);

        return std::make_tuple(R1, R2, R3, R4, Rg, Jg_f);
    }
    
}

#endif // __GABENCHMARK_SPECIALIZED_ALGORITHM_INVERSE_KINEMATICS_HPP__
