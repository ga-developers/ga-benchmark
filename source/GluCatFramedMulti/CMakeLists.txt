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

set(GluCatFramedMulti_SUCCESS true)

# Set (global) properties
set(GluCatFramedMulti_PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
)

# Set (global) include directories and libraries
set(GluCatFramedMulti_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/GluCat/install/usr/local/include" CACHE PATH "The include directory of the Clifford Algebra Templates (GluCat) library.")
set(GluCatFramedMulti_INCLUDE_EXTRA_DIR "")

if(NOT EXISTS ${GluCatFramedMulti_INCLUDE_DIR})
  # message(WARNING "The path defined in GluCatFramedMulti_INCLUDE_DIR doesn't exist.")
  set(GluCatFramedMulti_SUCCESS false)
endif()

set(GluCatFramedMulti_LIBS_INIT "")

# Set include directories and libraries for inverse kinematics
set(GluCatFramedMulti_AlgorithmInverseKinematics_INCLUDE_DIR "")
set(GluCatFramedMulti_AlgorithmInverseKinematics_LIBS_INIT "")

# Set include directories and libraries for ray tracing
set(GluCatFramedMulti_AlgorithmRayTracing_INCLUDE_DIR "")
set(GluCatFramedMulti_AlgorithmRayTracing_LIBS_INIT "")

# Set include directories and libraries for binary operations
set(GluCatFramedMulti_BinaryOperations_INCLUDE_DIR "")
set(GluCatFramedMulti_BinaryOperations_LIBS_INIT "")

# Set include directories and libraries for unary operations
set(GluCatFramedMulti_UnaryOperations_INCLUDE_DIR "")
set(GluCatFramedMulti_UnaryOperations_LIBS_INIT "")

# Job done!
if(${GluCatFramedMulti_SUCCESS})
  set(GluCatFramedMulti_ENABLED true CACHE BOOL "If set, the Clifford Algebra Templates (GluCat) library will be added to the benchmark.")
else()
  set(GluCatFramedMulti_ENABLED false CACHE BOOL "If set, the Clifford Algebra Templates (GluCat) library will be added to the benchmark." FORCE)
endif()