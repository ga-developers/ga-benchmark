# Copyright (C) 2018 ga-developers
# 
# Repository: https://github.com/ga-developers/ga-benchmark.git
# 
# This file is part of the GA-Benchmark project.
# 
# GA-Benchmark is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# GA-Benchmark is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GA-Benchmark. If not, see <https://www.gnu.org/licenses/>.

find_package(Eigen3 REQUIRED)

set(Garamon_ENABLED true CACHE BOOL "If set, the Geometric Algebra Recursive and Adaptive Monster (Garamon) is added to the benchmark.")
set(Garamon_CXX_STANDARD 14 CACHE STRING "The C++ standard whose features are requested to build Geometric Algebra Recursive and Adaptive Monster (Garamon) programs.")
set(Garamon_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/garamon/install/usr/local/include" CACHE PATH "The include directory of the Geometric Algebra Recursive and Adaptive Monster (Garamon).")
set(Garamon_INCLUDE_EXTRA_DIR ${EIGEN3_INCLUDE_DIR})

set(Garamon_LINK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/garamon/install/usr/local/lib")

# set(Garamon_EuclideanModel_D2_LIBS_INIT "" CACHE STRING "Euclidean geometric algebra 2-D.")
set(Garamon_EuclideanModel_D3_LIBS_INIT "${Garamon_LINK_DIR}/libe3ga.so" CACHE STRING "Euclidean geometric algebra 3-D.")
# set(Garamon_EuclideanModel_D4_LIBS_INIT "" CACHE STRING "Euclidean geometric algebra 4-D.")
# set(Garamon_EuclideanModel_D5_LIBS_INIT "" CACHE STRING "Euclidean geometric algebra 5-D.")

set(Garamon_ConformalModel_D2_LIBS_INIT "${Garamon_LINK_DIR}/libc2ga.so" CACHE STRING "Conformal geometric algebra 2-D.")
set(Garamon_ConformalModel_D3_LIBS_INIT "${Garamon_LINK_DIR}/libc3ga.so" CACHE STRING "Conformal geometric algebra 3-D.")

# set(Garamon_HomogeneousModel_D2_LIBS_INIT "" CACHE STRING "Homogeneous/Projective geometric algebra 2-D.")
# set(Garamon_HomogeneousModel_D3_LIBS_INIT "" CACHE STRING "Homogeneous/Projective geometric algebra 3-D.")
# set(Garamon_HomogeneousModel_D4_LIBS_INIT "" CACHE STRING "Homogeneous/Projective geometric algebra 4-D.")

set(Garamon_MinkowskiModel_D2_LIBS_INIT "${Garamon_LINK_DIR}/libst3ga.so" CACHE STRING "Spacetime algebra 2-D.")
# set(Garamon_MinkowskiModel_D3_LIBS_INIT "" CACHE STRING "Spacetime algebra 3-D.")