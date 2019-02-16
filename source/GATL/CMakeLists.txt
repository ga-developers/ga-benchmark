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

set(GATL_ENABLED true)

# Set (global) include directories and libraries
set(GATL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/GATL/repository/cpp/include" CACHE PATH "The include directory of the Geometric Algebra Template Library (GATL).")
set(GATL_INCLUDE_EXTRA_DIR "")

if(NOT EXISTS ${GATL_INCLUDE_DIR})
  message(WARNING "The path defined in GATL_INCLUDE_DIR doesn't exist.")
  set(GATL_ENABLED false)
endif()

set(GATL_LIBS_INIT "")

# Set include directories and libraries for products
set(GATL_Products_INCLUDE_DIR "")
set(GATL_Products_LIBS_INIT "")

# Set include directories and libraries for inverse kinematics
set(GATL_InverseKinematics_INCLUDE_DIR "")
set(GATL_InverseKinematics_LIBS_INIT "")

# Job done!
set(GATL_ENABLED ${GATL_ENABLED} CACHE BOOL "If set, the Geometric Algebra Template Library (GATL) is added to the benchmark.")