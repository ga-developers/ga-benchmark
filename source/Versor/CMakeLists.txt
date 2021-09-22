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

set(Versor_SUCCESS true)

# Find Versor library
find_library(Versor_LIBRARY NAMES vsr HINTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/Versor/install/usr/local/lib")
if(NOT EXISTS ${Versor_LIBRARY})
  # message(WARNING "The path defined in Versor_LIBRARY doesn't exist.")
  set(Versor_SUCCESS false)
endif()

# Set (global) properties
set(Versor_PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
)

# Set (global) include directories and libraries
set(Versor_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/Versor/install/usr/local/include" CACHE PATH "The include directory of the Versor library.")
set(Versor_INCLUDE_EXTRA_DIR "") # no dependencies

if(NOT EXISTS ${Versor_INCLUDE_DIR})
  # message(WARNING "The path defined in Versor_INCLUDE_DIR doesn't exist.")
  set(Versor_SUCCESS false)
endif()

set(Versor_LIBS_INIT ${Versor_LIBRARY})

# Set include directories and libraries for inverse kinematics
set(Versor_AlgorithmInverseKinematics_INCLUDE_DIR "")
set(Versor_AlgorithmInverseKinematics_LIBS_INIT "")

# Set include directories and libraries for ray tracing
set(Versor_AlgorithmRayTracing_INCLUDE_DIR "")
set(Versor_AlgorithmRayTracing_LIBS_INIT "")

# Set include directories and libraries for binary operations
set(Versor_BinaryOperations_INCLUDE_DIR "")
set(Versor_BinaryOperations_LIBS_INIT "")

# Set include directories and libraries for unary operations
set(Versor_UnaryOperations_INCLUDE_DIR "")
set(Versor_UnaryOperations_LIBS_INIT "")

# Job done!
if(${Versor_SUCCESS})
  set(Versor_ENABLED true CACHE BOOL "If set, the Versor library will be added to the benchmark.")
else()
  set(Versor_ENABLED false CACHE BOOL "If set, the Versor library will be added to the benchmark." FORCE)
endif()