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

set(Versor_ENABLED true)

# Find Versor library
find_library(Versor_LIBRARY NAMES vsr HINTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/Versor/install/usr/local/lib")
if(NOT EXISTS ${Versor_LIBRARY})
  message(WARNING "The path defined in Versor_LIBRARY doesn't exist.")
  set(Versor_ENABLED false)
endif()

# Set (global) include directories and libraries
set(Versor_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/Versor/install/usr/local/include" CACHE PATH "The include directory of the Versor library.")
set(Versor_INCLUDE_EXTRA_DIR "") # no dependencies

if(NOT EXISTS ${Versor_INCLUDE_DIR})
  message(WARNING "The path defined in Versor_INCLUDE_DIR doesn't exist.")
  set(Versor_ENABLED false)
endif()

set(Versor_LIBS_INIT ${Versor_LIBRARY})

# Set include directories and libraries for products
set(Versor_Products_INCLUDE_DIR "")
set(Versor_Products_LIBS_INIT "")

# Job done!
set(Versor_ENABLED ${Versor_ENABLED} CACHE BOOL "If set, the Versor library is added to the benchmark.")