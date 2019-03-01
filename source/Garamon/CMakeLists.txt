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

set(Garamon_ENABLED true)

# Set some constant values
set(Garamon_ConformalModel_MNEMONIC "c")
set(Garamon_EuclideanModel_MNEMONIC "e")
set(Garamon_HomogeneousModel_MNEMONIC "h")
set(Garamon_MinkowskiModel_MNEMONIC "m")

# Find required packages
find_package(Eigen3)
if(NOT ${EIGEN3_FOUND})
  # message(WARNING "Garamon requires Eigen3, which was not found.")
  set(Garamon_ENABLED false)
endif()

# Find Garamon libraries
foreach(MODEL ${MODELS_LIST})
  foreach(D_DIMENSIONS RANGE ${${MODEL}_MIN_D_DIMENSIONS} ${${MODEL}_MAX_D_DIMENSIONS})
    find_library(Garamon_${Garamon_${MODEL}_MNEMONIC}${D_DIMENSIONS}ga_LIBRARY NAMES ${Garamon_${MODEL}_MNEMONIC}${D_DIMENSIONS}ga HINTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/Garamon/install/usr/local/lib")
    if(NOT EXISTS ${Garamon_${Garamon_${MODEL}_MNEMONIC}${D_DIMENSIONS}ga_LIBRARY})
      # message(WARNING "The path defined in Garamon_${Garamon_${MODEL}_MNEMONIC}${D_DIMENSIONS}ga_LIBRARY doesn't exist.")
      set(Garamon_ENABLED false)
    endif()
  endforeach()
endforeach()

# Set (global) include directories and libraries
set(Garamon_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/Garamon/install/usr/local/include" CACHE PATH "The include directory of the Geometric Algebra Recursive and Adaptive Monster (Garamon).")
set(Garamon_INCLUDE_EXTRA_DIR ${EIGEN3_INCLUDE_DIR})

if(NOT EXISTS ${Garamon_INCLUDE_DIR})
  # message(WARNING "The path defined in Garamon_INCLUDE_DIR doesn't exist.")
  set(Garamon_ENABLED false)
endif()

set(Garamon_LIBS_INIT "")

# Set include directories and libraries for products
set(Garamon_Products_INCLUDE_DIR "")
set(Garamon_Products_LIBS_INIT "\${Garamon_\${Garamon_\${MODEL}_MNEMONIC}\${D_DIMENSIONS}ga_LIBRARY}")

# Set include directories and libraries for inverse kinematics
set(Garamon_AlgorithmInverseKinematics_INCLUDE_DIR "")
set(Garamon_AlgorithmInverseKinematics_LIBS_INIT "\${Garamon_\${Garamon_\${MODEL}_MNEMONIC}\${D_DIMENSIONS}ga_LIBRARY}")

# Job done!
set(Garamon_ENABLED ${Garamon_ENABLED} CACHE BOOL "If set, the Geometric Algebra Recursive and Adaptive Monster (Garamon) is added to the benchmark.")