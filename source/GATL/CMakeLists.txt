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

set(GATL_ENABLED true CACHE BOOL "If set, the Geometric Algebra Template Library (GATL) is added to the benchmark.")
set(GATL_INCLUDE_DIR ${GATL_INCLUDE_DIR} CACHE PATH "The include directory of the Geometric Algebra Template Library (GATL).")
set(GATL_LIBS_INIT "")  # pure template library
