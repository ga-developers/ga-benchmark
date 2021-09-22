# Copyright (C) ga-developers
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

set(GATL_SUCCESS true)

# Set (global) properties
set(GATL_PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
)

# Set (global) include directories and libraries
set(GATL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/GATL/install/include" CACHE PATH "The include directory of the Geometric Algebra Template Library (GATL).")
set(GATL_INCLUDE_EXTRA_DIR "")

if(NOT EXISTS ${GATL_INCLUDE_DIR})
  # message(WARNING "The path defined in GATL_INCLUDE_DIR doesn't exist.")
  set(GATL_SUCCESS false)
endif()

set(GATL_LIBS_INIT "")

# Set include directories and libraries for inverse kinematics
set(GATL_AlgorithmInverseKinematics_INCLUDE_DIR "")
set(GATL_AlgorithmInverseKinematics_LIBS_INIT "")

# Set include directories and libraries for ray tracing
set(GATL_AlgorithmRayTracing_INCLUDE_DIR "")
set(GATL_AlgorithmRayTracing_LIBS_INIT "")

# Set include directories and libraries for binary operations
set(GATL_BinaryOperations_INCLUDE_DIR "")
set(GATL_BinaryOperations_LIBS_INIT "")

# Set include directories and libraries for unary operations
set(GATL_UnaryOperations_INCLUDE_DIR "")
set(GATL_UnaryOperations_LIBS_INIT "")

# Job done!
if(${GATL_SUCCESS})
  set(GATL_ENABLED true CACHE BOOL "If set, the Geometric Algebra Template Library (GATL) will be added to the benchmark.")
else()
  set(GATL_ENABLED false CACHE BOOL "If set, the Geometric Algebra Template Library (GATL) will be added to the benchmark." FORCE)
endif()