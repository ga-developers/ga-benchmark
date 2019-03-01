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

set(GluCatMatrixMulti_ENABLED true)

# Set (global) include directories and libraries
set(GluCatMatrixMulti_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/GluCat/install/usr/local/include" CACHE PATH "The include directory of the Clifford Algebra Templates (GluCat) library.")
set(GluCatMatrixMulti_INCLUDE_EXTRA_DIR "") # no dependencies

if(NOT EXISTS ${GluCatMatrixMulti_INCLUDE_DIR})
  # message(WARNING "The path defined in GluCatMatrixMulti_INCLUDE_DIR doesn't exist.")
  set(GluCatMatrixMulti_ENABLED false)
endif()

set(GluCatMatrixMulti_LIBS_INIT "")

# Set include directories and libraries for products
set(GluCatMatrixMulti_Products_INCLUDE_DIR "")
set(GluCatMatrixMulti_Products_LIBS_INIT "")

# Set include directories and libraries for inverse kinematics
set(GluCatMatrixMulti_AlgorithmInverseKinematics_INCLUDE_DIR "")
set(GluCatMatrixMulti_AlgorithmInverseKinematics_LIBS_INIT "")

# Job done!
set(GluCatMatrixMulti_ENABLED ${GluCatMatrixMulti_ENABLED} CACHE BOOL "If set, the Clifford Algebra Templates (GluCat) library is added to the benchmark.")