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

set(Gaalet_SUCCESS true)

# Set (global) include directories and libraries
set(Gaalet_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/Gaalet/install/include/gaalet" CACHE PATH "The include directory of the Geometric Algebra ALgorithms Expression Templates (Gaalet).")
set(Gaalet_INCLUDE_EXTRA_DIR "")

if(NOT EXISTS ${Gaalet_INCLUDE_DIR})
  # message(WARNING "The path defined in Gaalet_INCLUDE_DIR doesn't exist.")
  set(Gaalet_SUCCESS false)
endif()

set(Gaalet_LIBS_INIT "")

# Set include directories and libraries for inverse kinematics
set(Gaalet_AlgorithmInverseKinematics_INCLUDE_DIR "")
set(Gaalet_AlgorithmInverseKinematics_LIBS_INIT "")

# Set include directories and libraries for binary operations
set(Gaalet_BinaryOperations_INCLUDE_DIR "")
set(Gaalet_BinaryOperations_LIBS_INIT "")

# Set include directories and libraries for unary operations
set(Gaalet_UnaryOperations_INCLUDE_DIR "")
set(Gaalet_UnaryOperations_LIBS_INIT "")

# Job done!
if(${Gaalet_SUCCESS})
  set(Gaalet_ENABLED true CACHE BOOL "If set, the Geometric Algebra ALgorithms Expression Templates (Gaalet) will be added to the benchmark.")
else()
  set(Gaalet_ENABLED false CACHE BOOL "If set, the Geometric Algebra ALgorithms Expression Templates (Gaalet) will be added to the benchmark." FORCE)
endif()