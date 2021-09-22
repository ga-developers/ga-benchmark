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

#ifndef __GABM_SPECIALIZED_ALGORITHM_RAY_TRACING_HPP__
#define __GABM_SPECIALIZED_ALGORITHM_RAY_TRACING_HPP__

/**
struct Line {
    gabm::location_coords_t origin;
    gabm::direction_coords_t direction;
};

struct PointPair {
    gabm::location_coords_t p1;
    gabm::location_coords_t p2;
    bool ok;
};

struct Sphere {
    gabm::location_coords_t center;
    gabm::real_t radius;
};

GABM_ALWAYS_INLINE gabm::real_t dot(gabm::direction_coords_t const &arg1, gabm::direction_coords_t const &arg2) {
    return arg1[0] * arg2[0] + arg1[1] * arg2[1] + arg1[2] * arg2[2];
}

GABM_ALWAYS_INLINE gabm::direction_coords_t unit(gabm::direction_coords_t const &arg) {
    gabm::real_t aux = 1 / sqrt(dot(arg, arg));
    return gabm::direction_coords_t{arg[0] * aux, arg[1] * aux, arg[2] * aux};
}

GABM_DEFINE_RAY_TRACING_CHECK_INSIDE_SPHERE(sphere, point) {
    gabm::direction_coords_t l{sphere.center[0] - point[0], sphere.center[1] - point[1], sphere.center[2] - point[2]};
    return dot(l, l) <= (sphere.radius * sphere.radius);
}

GABM_DEFINE_RAY_TRACING_CHECK_PAIR_OF_POINTS(candidate) {
    return candidate.ok;
}

GABM_DEFINE_RAY_TRACING_COMPUTE_COSINE(unit_direction_1, unit_direction_2) {
    return dot(unit_direction_1, unit_direction_2);
}

GABM_DEFINE_RAY_TRACING_COMPUTE_INTERSECTION(sphere, ray) {
    gabm::direction_coords_t l{sphere.center[0] - ray.origin[0], sphere.center[1] - ray.origin[1], sphere.center[2] - ray.origin[2]};
    
    gabm::real_t tca = dot(l, ray.direction);
    if (tca < 0) return PointPair{gabm::location_coords_t{}, gabm::location_coords_t{}, false};
    
    gabm::real_t radius2 = sphere.radius * sphere.radius;
    gabm::real_t d2 = dot(l, l) - tca * tca;
    if (d2 > radius2) return PointPair{gabm::location_coords_t{}, gabm::location_coords_t{}, false};
    
    gabm::real_t thc = sqrt(radius2 - d2);
    gabm::real_t t0 = tca - thc;
    gabm::real_t t1 = tca + thc;

    return PointPair{gabm::location_coords_t{ray.origin[0] + ray.direction[0] * t0, ray.origin[1] + ray.direction[1] * t0, ray.origin[2] + ray.direction[2] * t0}, gabm::location_coords_t{ray.origin[0] + ray.direction[0] * t1, ray.origin[1] + ray.direction[1] * t1, ray.origin[2] + ray.direction[2] * t1}, true};
}

GABM_DEFINE_RAY_TRACING_COMPUTE_SIGNED_DISTANCE(reference_point, reference_direction, target_point) {
    return dot(gabm::direction_coords_t{target_point[0] - reference_point[0], target_point[1] - reference_point[1], target_point[2] - reference_point[2]}, reference_direction);
}

GABM_DEFINE_RAY_TRACING_DISSECT_POINT_PAIR(point_pair) {
    return std::make_tuple(point_pair.p1, point_pair.p2);
}

GABM_DEFINE_RAY_TRACING_MAKE_RAY_LINE(origin, direction) {
    return Line{origin, direction};
}

GABM_DEFINE_RAY_TRACING_MAKE_SPHERE(location_coords, radius) {
    return Sphere{location_coords, radius};
}

GABM_DEFINE_RAY_TRACING_MAKE_UNIT_FLAT_POINT(location_coords) {
    return (location_coords);
}

GABM_DEFINE_RAY_TRACING_MAKE_UNIT_FREE_VECTOR(direction_coords) {
    return unit(direction_coords);
}

GABM_DEFINE_RAY_TRACING_REFLECT(unit_direction, unit_normal) {
    gabm::real_t aux = 2 * dot(unit_direction, unit_normal);
    return unit(gabm::direction_coords_t{unit_direction[0] - unit_normal[0] * aux, unit_direction[1] - unit_normal[1] * aux, unit_direction[2] - unit_normal[2] * aux});
}

GABM_DEFINE_RAY_TRACING_REFRACT(unit_direction, unit_normal, refractive_index) {
    gabm::real_t cosi = -dot(unit_normal, unit_direction);
    gabm::real_t aux = refractive_index *  cosi - sqrt(1 - refractive_index * refractive_index * (1 - cosi * cosi));
    return unit(gabm::direction_coords_t{unit_direction[0] * refractive_index + unit_normal[0] * aux, unit_direction[1] * refractive_index + unit_normal[1] * aux, unit_direction[2] * refractive_index + unit_normal[2] * aux});
}

GABM_DEFINE_RAY_TRACING_TRANSLATE(point, unit_direction, delta) {
    return gabm::location_coords_t{point[0] + unit_direction[0] * delta, point[1] + unit_direction[1] * delta, point[2] + unit_direction[2] * delta};
}

GABM_DEFINE_RAY_TRACING_UNIT_DIRECTION_FROM_POINT(reference_point, target_sphere) {
    return unit(gabm::direction_coords_t{target_sphere.center[0] - reference_point[0], target_sphere.center[1] - reference_point[1], target_sphere.center[2] - reference_point[2]});
}

GABM_DEFINE_RAY_TRACING_UNIT_DIRECTION_FROM_SPHERE(reference_sphere, target_point) {
    return unit(gabm::direction_coords_t{target_point[0] - reference_sphere.center[0], target_point[1] - reference_sphere.center[1], target_point[2] - reference_sphere.center[2]});
}
/*/
template<typename SphereBladeType>
GABM_INLINE decltype(auto) sphere_center(SphereBladeType const &sphere_) {
    auto [lazy, sphere] = make_lazy_context_tuple(sphere_);
    auto aux = lcont(ni, sphere);
    return lazy.eval(igp(gp(gp(sphere, ni), sphere), -c<2> * sp(aux, aux)) ^ ni);
}

GABM_DEFINE_RAY_TRACING_CHECK_INSIDE_SPHERE(sphere_, point_) {
    auto [lazy, sphere, point] = make_lazy_context_tuple(sphere_, point_);
    return lazy.eval(sp(dual(sphere), point)) >= 0;
}

GABM_DEFINE_RAY_TRACING_CHECK_PAIR_OF_POINTS(candidate_) {
    auto [lazy, candidate] = make_lazy_context_tuple(candidate_);
    auto aux = lcont(ni, candidate);
    if (lazy.eval(sp(aux, aux)) <= 0) throw std::runtime_error("Eeeeeeita!");
    return lazy.eval(sp(sp(candidate, candidate), inv(sp(aux, aux)))) > 0;
}

GABM_DEFINE_RAY_TRACING_COMPUTE_COSINE(unit_direction_1_, unit_direction_2_) {
    auto [lazy, unit_direction_1, unit_direction_2] = make_lazy_context_tuple(unit_direction_1_, unit_direction_2_);
    return lazy.eval(sp(lcont(no, unit_direction_1), lcont(no, unit_direction_2)));
}

GABM_DEFINE_RAY_TRACING_COMPUTE_INTERSECTION(sphere_, ray_) {
    auto [lazy, sphere, ray] = make_lazy_context_tuple(sphere_, ray_);
    return lazy.eval(lcont(dual(ray), sphere));
}

GABM_DEFINE_RAY_TRACING_COMPUTE_SIGNED_DISTANCE(reference_point_, reference_direction_, target_point_) {
    auto [lazy, reference_point, reference_direction, target_point] = make_lazy_context_tuple(reference_point_, reference_direction_, target_point_);
    return lazy.eval(sp(lcont(no, target_point - reference_point), lcont(no, reference_direction)));
}

GABM_DEFINE_RAY_TRACING_DISSECT_POINT_PAIR(point_pair_) {
    auto [lazy, point_pair] = make_lazy_context_tuple(point_pair_);
    auto aux = inv(lcont(-ni, point_pair));
    auto v1 = gp(point_pair, aux);
    auto v2 = gp(sqrt(sp(point_pair, point_pair)), aux);
    return std::make_tuple(lazy.eval(take_grade(v1 - v2, c<1>) ^ ni), lazy.eval(take_grade(v1 + v2, c<1>) ^ ni)); //TODO Não deveria precisar de take_grade e a coordenada homogênea deveria ser c<1>
}

GABM_DEFINE_RAY_TRACING_MAKE_RAY_LINE(origin_, direction_) {
    auto [lazy, origin, direction] = make_lazy_context_tuple(origin_, direction_);
    return lazy.eval(origin ^ lcont(-no, direction));
}

GABM_DEFINE_RAY_TRACING_MAKE_SPHERE(location_coords, radius) {
    return undual(point(location_coords[0], location_coords[1], location_coords[2]) - (radius * radius) * (ni / c<2>));
}

GABM_DEFINE_RAY_TRACING_MAKE_UNIT_FLAT_POINT(location_coords) {
    return point(location_coords[0], location_coords[1], location_coords[2]) ^ ni;
}

GABM_DEFINE_RAY_TRACING_MAKE_UNIT_FREE_VECTOR(direction_coords) {
    return euclidean::unit(euclidean_vector(direction_coords[0], direction_coords[1], direction_coords[2])) ^ ni;
}

GABM_DEFINE_RAY_TRACING_REFLECT(unit_direction, unit_normal) {
    return euclidean::unit(unit_direction - unit_normal * (c<2> * sp(lcont(no, unit_direction), lcont(no, unit_normal))));
}

GABM_DEFINE_RAY_TRACING_REFRACT(unit_direction, unit_normal, refractive_index) {
    gabm::real_t cosi = -sp(lcont(no, unit_normal), lcont(no, unit_direction));
    return euclidean::unit(unit_direction * refractive_index + unit_normal * (refractive_index *  cosi - sqrt(c<1> - refractive_index * refractive_index * (c<1> - cosi * cosi)))); 
}

GABM_DEFINE_RAY_TRACING_TRANSLATE(point, unit_direction, delta) {
    return apply_rotor(c<1> - (delta / c<2>) * unit_direction, point);
}

GABM_DEFINE_RAY_TRACING_UNIT_DIRECTION_FROM_POINT(reference_point, target_sphere) {
    return euclidean::unit(sphere_center(target_sphere) - reference_point);
}

GABM_DEFINE_RAY_TRACING_UNIT_DIRECTION_FROM_SPHERE(reference_sphere, target_point) {
    return euclidean::unit(target_point - sphere_center(reference_sphere));
}
/**/

GABM_DEFINE_ALGORITHM_RAY_TRACING()

#endif // __GABM_SPECIALIZED_ALGORITHM_RAY_TRACING_HPP__
