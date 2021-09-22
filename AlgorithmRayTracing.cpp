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

#define GABM_ITERATIONS 1

#include "Macros.hpp"
#include "Types.hpp"
#include <SpecializedAlgebra.hpp>

#if !defined(GABM_MODEL_NOT_IMPLEMENTED)

    #include "Utils.hpp"

    #define GABM_DEFINE_RAY_TRACING_CHECK_INSIDE_SPHERE(SPHERE, POINT) \
        template<typename SphereBladeType, typename FlatPointBladeType> \
        GABM_INLINE bool GABM_RayTracing_CheckInsideSphere(SphereBladeType const &SPHERE, FlatPointBladeType const &POINT)

    #define GABM_DEFINE_RAY_TRACING_CHECK_PAIR_OF_POINTS(CANDIDATE) \
        template<typename PrimalTwoBladeType> \
        GABM_INLINE bool GABM_RayTracing_CheckPairOfPoints(PrimalTwoBladeType const &CANDIDATE)

    #define GABM_DEFINE_RAY_TRACING_COMPUTE_COSINE(UNIT_DIRECTION_1, UNIT_DIRECTION_2) \
        template<typename FirstFreeVectorBladeType, typename SecondFreeVectorBladeType> \
        GABM_INLINE gabm::real_t GABM_RayTracing_ComputeCosine(FirstFreeVectorBladeType const &UNIT_DIRECTION_1, SecondFreeVectorBladeType const &UNIT_DIRECTION_2)

    #define GABM_DEFINE_RAY_TRACING_COMPUTE_INTERSECTION(SPHERE, RAY) \
        template<typename SphereBladeType, typename LineBladeType> \
        GABM_INLINE decltype(auto) GABM_RayTracing_ComputeIntersection(SphereBladeType const &SPHERE, LineBladeType const &RAY)

    #define GABM_DEFINE_RAY_TRACING_COMPUTE_SIGNED_DISTANCE(REFERENCE_POINT, REFERENCE_DIRECTION, TARGET_POINT) \
        template<typename ReferenceFlatPointBladeType, typename FreeVectorBladeType, typename TargetFlatPointBladeType> \
        GABM_INLINE gabm::real_t GABM_RayTracing_ComputeSignedDistance(ReferenceFlatPointBladeType const &REFERENCE_POINT, FreeVectorBladeType const &REFERENCE_DIRECTION, TargetFlatPointBladeType const &TARGET_POINT)

    #define GABM_DEFINE_RAY_TRACING_DISSECT_POINT_PAIR(POINT_PAIR) \
        template<typename PointPairBladeType> \
        GABM_INLINE decltype(auto) GABM_RayTracing_DissectPointPair(PointPairBladeType const &POINT_PAIR)

    #define GABM_DEFINE_RAY_TRACING_MAKE_RAY_LINE(ORIGIN, DIRECTION) \
        template<typename FlatPointBladeType, typename FreeVectorBladeType> \
        GABM_INLINE decltype(auto) GABM_RayTracing_MakeRayLine(FlatPointBladeType const &ORIGIN, FreeVectorBladeType const &DIRECTION)

    #define GABM_DEFINE_RAY_TRACING_MAKE_SPHERE(LOCATION_COORDS, RADIUS) \
        GABM_INLINE decltype(auto) GABM_RayTracing_MakeSphere(gabm::location_coords_t const &LOCATION_COORDS, gabm::real_t RADIUS)

    #define GABM_DEFINE_RAY_TRACING_MAKE_UNIT_FLAT_POINT(LOCATION_COORDS) \
        GABM_INLINE decltype(auto) GABM_RayTracing_MakeUnitFlatPoint(gabm::location_coords_t const &LOCATION_COORDS)

    #define GABM_DEFINE_RAY_TRACING_MAKE_UNIT_FREE_VECTOR(DIRECTION_COORDS) \
        GABM_INLINE decltype(auto) GABM_RayTracing_MakeUnitFreeVector(gabm::direction_coords_t const &DIRECTION_COORDS)

    #define GABM_DEFINE_RAY_TRACING_REFLECT(UNIT_DIRECTION, UNIT_NORMAL) \
        template<typename DirectionFreeVectorBladeType, typename NormalFreeVectorBladeType> \
        GABM_INLINE decltype(auto) GABM_RayTracing_Reflect(DirectionFreeVectorBladeType const &UNIT_DIRECTION, NormalFreeVectorBladeType const &UNIT_NORMAL)

    #define GABM_DEFINE_RAY_TRACING_REFRACT(UNIT_DIRECTION, UNIT_NORMAL, REFRACTIVE_INDEX) \
        template<typename DirectionFreeVectorBladeType, typename NormalFreeVectorBladeType> \
        GABM_INLINE decltype(auto) GABM_RayTracing_Refract(DirectionFreeVectorBladeType const &UNIT_DIRECTION, NormalFreeVectorBladeType const &UNIT_NORMAL, gabm::real_t const REFRACTIVE_INDEX)

    #define GABM_DEFINE_RAY_TRACING_TRANSLATE(POINT, UNIT_DIRECTION, DELTA) \
        template<typename FlatPointBladeType, typename FreeVectorBladeType> \
        GABM_INLINE decltype(auto) GABM_RayTracing_Translate(FlatPointBladeType const &POINT, FreeVectorBladeType const &UNIT_DIRECTION, gabm::real_t const DELTA)

    #define GABM_DEFINE_RAY_TRACING_UNIT_DIRECTION_FROM_POINT(REFERENCE_POINT, TARGET_SPHERE) \
        template<typename FlatPointBladeType, typename SphereBladeType> \
        GABM_INLINE decltype(auto) GABM_RayTracing_UnitDirectionFromPoint(FlatPointBladeType const &REFERENCE_POINT, SphereBladeType const &TARGET_SPHERE)

    #define GABM_DEFINE_RAY_TRACING_UNIT_DIRECTION_FROM_SPHERE(REFERENCE_SPHERE, TARGET_POINT) \
        template<typename SphereBladeType, typename FlatPointBladeType> \
        GABM_INLINE decltype(auto) GABM_RayTracing_UnitDirectionFromSphere(SphereBladeType const &REFERENCE_SPHERE, FlatPointBladeType const &TARGET_POINT)

    #define GABM_DEFINE_ALGORITHM_RAY_TRACING() \
        class GABM_RayTracing_Color { \
        public: \
            \
            gabm::real_t r, g, b; \
            \
            GABM_ALWAYS_INLINE GABM_RayTracing_Color(gabm::real_t &&r_, gabm::real_t &&g_, gabm::real_t &&b_) : \
                r(std::move(r_)), g(std::move(g_)), b(std::move(b_)) { \
            } \
            \
            GABM_ALWAYS_INLINE GABM_RayTracing_Color() : \
                GABM_RayTracing_Color(0, 0, 0) { \
            } \
            \
            GABM_ALWAYS_INLINE GABM_RayTracing_Color(GABM_RayTracing_Color const &) = default; \
            GABM_ALWAYS_INLINE GABM_RayTracing_Color(GABM_RayTracing_Color &&) = default; \
            \
            GABM_ALWAYS_INLINE GABM_RayTracing_Color & operator=(GABM_RayTracing_Color const &) = default; \
            GABM_ALWAYS_INLINE constexpr GABM_RayTracing_Color & operator=(GABM_RayTracing_Color &&) = default; \
            \
            GABM_ALWAYS_INLINE GABM_RayTracing_Color operator*(gabm::real_t const value) const { \
                return GABM_RayTracing_Color(r * value, g * value, b * value); \
            } \
            \
            GABM_ALWAYS_INLINE GABM_RayTracing_Color operator*(GABM_RayTracing_Color const &other) const { \
                return GABM_RayTracing_Color(r * other.r, g * other.g, b * other.b); \
            } \
            \
            GABM_ALWAYS_INLINE GABM_RayTracing_Color operator+(GABM_RayTracing_Color const &other) const { \
                return GABM_RayTracing_Color(r + other.r, g + other.g, b + other.b); \
            } \
            \
            GABM_ALWAYS_INLINE GABM_RayTracing_Color& operator+=(GABM_RayTracing_Color const &other) { \
                r += other.r; g += other.g; b += other.b; \
                return *this; \
            } \
        }; \
        \
        class GABM_RayTracing_Sphere { \
        public: \
            \
            using sphere_t = decltype(GABM_RayTracing_MakeSphere(gabm::location_coords_t(), gabm::real_t())); \
            \
            sphere_t blade; \
            GABM_RayTracing_Color surface_color, emission_color; \
            gabm::real_t transparency, reflectivity, refractive_index; \
            \
            GABM_RayTracing_Sphere(gabm::location_coords_t &&center_, gabm::real_t &&radius_, GABM_RayTracing_Color &&surface_color_, gabm::real_t &&reflectivity_, gabm::real_t &&transparency_, gabm::real_t &&refractive_index_ = std::numeric_limits<gabm::real_t>::quiet_NaN(), GABM_RayTracing_Color &&emission_color_ = GABM_RayTracing_Color(0.0, 0.0, 0.0)) : \
                blade(GABM_RayTracing_MakeSphere(std::move(center_), std::move(radius_))), \
                surface_color(std::move(surface_color_)), emission_color(std::move(emission_color_)), \
                transparency(std::move(transparency_)), reflectivity(std::move(reflectivity_)), refractive_index(std::move(refractive_index_)) { \
            } \
        }; \
        \
        GABM_DEFINE_ENTRY_GENERATOR(scene) { \
            return std::vector<GABM_RayTracing_Sphere>{ \
                /* Center, radius, surface color, reflectivity, transparency, refractive index, emission color */ \
                GABM_RayTracing_Sphere(gabm::location_coords_t{ 0.0, -10004.0, -20.0}, 10000.0, GABM_RayTracing_Color(0.20, 0.20, 0.20), 0.0, 0.0), \
                GABM_RayTracing_Sphere(gabm::location_coords_t{ 0.0,      0.0, -20.0},     4.0, GABM_RayTracing_Color(1.00, 0.32, 0.36), 1.0, 0.5, 1.1), \
                GABM_RayTracing_Sphere(gabm::location_coords_t{ 5.0,     -1.0, -15.0},     2.0, GABM_RayTracing_Color(0.90, 0.76, 0.46), 1.0, 0.0), \
                GABM_RayTracing_Sphere(gabm::location_coords_t{ 5.0,      0.0, -25.0},     3.0, GABM_RayTracing_Color(0.65, 0.77, 0.97), 1.0, 0.0), \
                GABM_RayTracing_Sphere(gabm::location_coords_t{-5.5,      0.0, -15.0},     3.0, GABM_RayTracing_Color(0.13, 0.69, 0.30), 1.0, 0.0), \
                /* Light source */ \
                GABM_RayTracing_Sphere(gabm::location_coords_t{ 0.0,     20.0, -30.0},     3.0, GABM_RayTracing_Color(0.00, 0.00, 0.00), 0.0, 0.0, 0.0, GABM_RayTracing_Color(1.00, 1.00, 1.00)) \
            }; \
        } \
        \
        GABM_DEFINE_ENTRY_GENERATOR(image_width) { \
            return 640; \
        } \
        \
        GABM_DEFINE_ENTRY_GENERATOR(image_height) { \
            return 480; \
        } \
        \
        GABM_DEFINE_ENTRY_GENERATOR(image) { \
            return std::vector<GABM_RayTracing_Color>(640 * 480, GABM_RayTracing_Color(0.0, 0.0, 0.0)); \
        } \
        \
        GABM_DECLARE_INPUT_ENTRIES(scene) \
        GABM_DECLARE_INPUT_ENTRIES(image_width) \
        GABM_DECLARE_INPUT_ENTRIES(image_height) \
        GABM_DECLARE_RESULTING_ENTRIES(image) \
        \
        GABM_BIND_ARGUMENTS_FOR_OPERATION(Algorithm, RayTracing, scene, image, image_width, image_height) \
        \
        GABM_INLINE decltype(auto) GABM_Algorithm_RayTracing_Wrapper(std::vector<GABM_RayTracing_Sphere> const &, std::vector<GABM_RayTracing_Color> &, std::uint32_t const, std::uint32_t const); \
        \
        GABM_DEFINE_OPERATION(Algorithm, RayTracing, _:_) \
        \
        template<typename FlatPointBladeType, typename FreeVectorBladeType> \
        GABM_RayTracing_Color GABM_RayTracing_Trace(FlatPointBladeType const &ray_origin, FreeVectorBladeType const &ray_direction, std::vector<GABM_RayTracing_Sphere> const &spheres, std::int32_t const depth) { \
            using sphere_t = typename GABM_RayTracing_Sphere::sphere_t; \
            using line_t = decltype(GABM_RayTracing_MakeRayLine(FlatPointBladeType(), FreeVectorBladeType())); \
            using point_pair_t = decltype(GABM_RayTracing_ComputeIntersection(sphere_t(), line_t())); \
            using flat_point_tuple_t = decltype(GABM_RayTracing_DissectPointPair(point_pair_t())); \
            using flat_point_t = std::tuple_element_t<0, flat_point_tuple_t>; \
            using free_vector_t = decltype(GABM_RayTracing_UnitDirectionFromSphere(sphere_t(), flat_point_t())); \
            \
            constexpr std::int32_t MAX_RAY_DEPTH = 5; \
            constexpr gabm::real_t NEXT_RAY_ORIGIN_BIAS = 1e-4; \
            \
            line_t ray = GABM_RayTracing_MakeRayLine(ray_origin, ray_direction); \
            \
            /* Find closest intersection of the ray with spheres in the scene */ \
            point_pair_t curr_intersection; \
            gabm::real_t hit_distance_sqr = std::numeric_limits<gabm::real_t>::max(); \
            flat_point_t hit_point, curr_hit_point1, curr_hit_point2; \
            GABM_RayTracing_Sphere const *hit_sphere_ptr = nullptr; \
            for (auto const &curr_sphere : spheres) { \
                curr_intersection = GABM_RayTracing_ComputeIntersection(curr_sphere.blade, ray); \
                if (GABM_RayTracing_CheckPairOfPoints(curr_intersection)) { \
                    std::tie(curr_hit_point1, curr_hit_point2) = GABM_RayTracing_DissectPointPair(curr_intersection); \
                    gabm::real_t distance_sqr1 = GABM_RayTracing_ComputeSignedDistance(ray_origin, ray_direction, curr_hit_point1); \
                    gabm::real_t distance_sqr2 = GABM_RayTracing_ComputeSignedDistance(ray_origin, ray_direction, curr_hit_point2); \
                    if (distance_sqr1 < 0) { \
                        if (distance_sqr2 < hit_distance_sqr) { \
                            hit_distance_sqr = distance_sqr2; \
                            hit_point = curr_hit_point2; \
                            hit_sphere_ptr = &curr_sphere; \
                        } \
                    } \
                    else { \
                        if (distance_sqr1 < hit_distance_sqr) { \
                            hit_distance_sqr = distance_sqr1; \
                            hit_point = curr_hit_point1; \
                            hit_sphere_ptr = &curr_sphere; \
                        } \
                    } \
                } \
            } \
            \
            /* If there's no intersection then return background color */ \
            if (hit_sphere_ptr == nullptr) { \
                return GABM_RayTracing_Color(1.0, 1.0, 1.0); \
            } \
            \
            /* Compute the color of the ray */ \
            bool hit_inside = GABM_RayTracing_CheckInsideSphere(hit_sphere_ptr->blade, ray_origin); \
            free_vector_t hit_normal = hit_inside ? GABM_RayTracing_UnitDirectionFromPoint(hit_point, hit_sphere_ptr->blade) : GABM_RayTracing_UnitDirectionFromSphere(hit_sphere_ptr->blade, hit_point); \
            GABM_RayTracing_Color ray_color = hit_sphere_ptr->emission_color; \
            if ((hit_sphere_ptr->transparency > 0 || hit_sphere_ptr->reflectivity > 0) && depth < MAX_RAY_DEPTH) { \
                GABM_RayTracing_Color reflection = GABM_RayTracing_Trace(GABM_RayTracing_Translate(hit_point, hit_normal, NEXT_RAY_ORIGIN_BIAS), GABM_RayTracing_Reflect(ray_direction, hit_normal), spheres, depth + 1); \
                GABM_RayTracing_Color refraction = GABM_RayTracing_Color(0.0, 0.0, 0.0); \
                if (hit_sphere_ptr->transparency > 0) { \
                    refraction = GABM_RayTracing_Trace(GABM_RayTracing_Translate(hit_point, hit_normal, -NEXT_RAY_ORIGIN_BIAS), GABM_RayTracing_Refract(ray_direction, hit_normal, hit_inside ? hit_sphere_ptr->refractive_index : 1 / hit_sphere_ptr->refractive_index), spheres, depth + 1); \
                } \
                gabm::real_t fresnel_aux = 1 + GABM_RayTracing_ComputeCosine(ray_direction, hit_normal); \
                gabm::real_t fresnel_effect = 0.1 + (fresnel_aux * fresnel_aux * fresnel_aux) * 0.9; \
                ray_color += (reflection * fresnel_effect + refraction * ((1 - fresnel_effect) * hit_sphere_ptr->transparency)) * hit_sphere_ptr->surface_color; \
            } \
            else { \
                line_t light_ray; \
                free_vector_t light_direction; \
                for (auto const &light : spheres) { \
                    if (light.emission_color.r > 0 || light.emission_color.g > 0 || light.emission_color.b > 0) { \
                        light_direction = GABM_RayTracing_UnitDirectionFromPoint(hit_point, light.blade); \
                        light_ray = GABM_RayTracing_MakeRayLine(GABM_RayTracing_Translate(hit_point, hit_normal, NEXT_RAY_ORIGIN_BIAS), light_direction); \
                        bool shadow = false; \
                        for (auto const &other_sphere : spheres) { \
                            if (&light != &other_sphere && GABM_RayTracing_CheckPairOfPoints(GABM_RayTracing_ComputeIntersection(other_sphere.blade, light_ray))) { \
                                shadow = true; \
                                break; \
                            } \
                        } \
                        if (!shadow) { \
                            ray_color += hit_sphere_ptr->surface_color * std::max(gabm::real_t(0), GABM_RayTracing_ComputeCosine(hit_normal, light_direction)) * light.emission_color; \
                        } \
                    } \
                } \
            } \
            \
            return ray_color; \
        } \
        \
        GABM_ALWAYS_INLINE decltype(auto) GABM_Algorithm_RayTracing_Wrapper(std::vector<GABM_RayTracing_Sphere> const &spheres, std::vector<GABM_RayTracing_Color> &image, std::uint32_t const width, std::uint32_t const height) { \
            gabm::real_t inv_width = 1 / gabm::real_t(width), inv_height = 1 / gabm::real_t(height); \
            gabm::real_t fov = 30, aspect_ratio = width / gabm::real_t(height); \
            gabm::real_t angle = tan(gabm::pi * 0.5 * fov / 180); \
            \
            std::fill(image.begin(), image.end(), GABM_RayTracing_Color(0.0, 0.0, 0.0)); \
            \
            auto pixel_itr = image.begin(); \
            for (std::uint32_t y = 0; y < height; ++y) { \
                for (std::uint32_t x = 0; x < width; ++x, ++pixel_itr) { \
                    gabm::real_t xx = (2 * ((x + 0.5) * inv_width) - 1) * angle * aspect_ratio; \
                    gabm::real_t yy = (1 - 2 * ((y + 0.5) * inv_height)) * angle; \
                    *pixel_itr = GABM_RayTracing_Trace(GABM_RayTracing_MakeUnitFlatPoint(gabm::location_coords_t{0, 0, 0}), GABM_RayTracing_MakeUnitFreeVector(gabm::direction_coords_t{xx, yy, -1}), spheres, 0); \
                } \
            } \
            \
            /* Write the image to a PPM image */ \
            /**/ \
            std::ofstream ofs("./GABenchmark_AlgorithmRayTracing_ConformalModel_D3_debug.ppm", std::ios::out | std::ios::binary); \
            ofs << "P6\n" << width << " " << height << "\n255\n"; \
            for (GABM_RayTracing_Color const &pixel : image) { \
                ofs << (std::uint8_t)(std::min(gabm::real_t(1), pixel.r) * 255) << (std::uint8_t)(std::min(gabm::real_t(1), pixel.g) * 255) << (std::uint8_t)(std::min(gabm::real_t(1), pixel.b) * 255); \
            } \
            ofs.close(); \
            /**/ \
            \
            return image; \
        }

    #define GABM_REPORT_ALGORITHM_RAY_TRACING_IS_NOT_IMPLEMENTED() \
        GABM_REPORT_OPERATION_IS_NOT_IMPLEMENTED(Algorithm, RayTracing, _:_)
    
    #define GABM_REPORT_ALGORITHM_RAY_TRACING_LEADS_TO_COMPILATION_ERROR() \
        GABM_REPORT_OPERATION_LEADS_TO_COMPILATION_ERROR(Algorithm, RayTracing, _:_)

    #include <SpecializedAlgorithmRayTracing.hpp>

#else

    GABM_SKIP_OPERATION_WHEN_MODEL_IS_NOT_IMPLEMENTED(Algorithm, RayTracing, _:_)

#endif

GABM_ASSERT_OPERATION_DEFINITION(Algorithm, RayTracing)

GABM_MAIN()
