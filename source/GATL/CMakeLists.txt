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

set(GATL_ENABLED false CACHE BOOL "If set, the Geometric Algebra Template Library (GATL) is added to the benchmark.")
set(GATL_CXX_STANDARD 17 CACHE STRING "The C++ standard whose features are requested to build Geometric Algebra Template Library (GATL) programs.")
set(GATL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/gatl/cpp/include" CACHE PATH "The include directory of the Geometric Algebra Template Library (GATL).")
set(GATL_INCLUDE_EXTRA_DIR "") # no dependencies

foreach(MODEL ${MODELS_LIST})
  foreach(D_DIMENSIONS RANGE ${${MODEL}_MIN_D_DIMENSIONS} ${${MODEL}_MAX_D_DIMENSIONS})
    set(GATL_${MODEL}_D${D_DIMENSIONS}_LIBS_INIT "") # pure template library
  endforeach()
endforeach()
