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

cmake_minimum_required(VERSION 3.10)

project(GA-Benchmark)

include(CTest)

# Implement some useful macros
macro(subdirlist RESULT PARENTDIR)
  file(GLOB CHILDREN RELATIVE ${PARENTDIR} ${PARENTDIR}/*)
  set(${RESULT} "")
  foreach(CHILD ${CHILDREN})
    if(IS_DIRECTORY ${PARENTDIR}/${CHILD})
      list(APPEND ${RESULT} ${CHILD})
    endif()
  endforeach()
endmacro()

# Find required packages
find_package(benchmark REQUIRED)
find_package(Threads REQUIRED)

# Find tested libraries
subdirlist(LIBRARIES_LIST "${PROJECT_SOURCE_DIR}/source")

message(STATUS "")
message(STATUS "Geometric Algebra Libraries:")
foreach(LIBRARY ${LIBRARIES_LIST})
  if(EXISTS "${PROJECT_SOURCE_DIR}/source/${LIBRARY}/CMakeLists.txt")
    include("${PROJECT_SOURCE_DIR}/source/${LIBRARY}/CMakeLists.txt")
    if(DEFINED ${LIBRARY}_ENABLED)
      message(STATUS "  - " ${LIBRARY})
    endif()
  endif()
endforeach()

# Create benchmarks...
message(STATUS "")
message(STATUS "Benchmarks:")

# ... for products
set(OPERATION Products)

set(Products_MODELS_LIST
  Euclidean
  Conformal
  Homogeneous
  Minkowski
)

set(Products_Euclidean_MAX_D_DIMENSIONS 5)
set(Products_Conformal_MAX_D_DIMENSIONS 3)
set(Products_Homogeneous_MAX_D_DIMENSIONS 4)
set(Products_Minkowski_MAX_D_DIMENSIONS 3)

foreach(LIBRARY ${LIBRARIES_LIST})
  if(${${LIBRARY}_ENABLED})
    message(STATUS "  - " ${LIBRARY})
    message(STATUS "    - " ${OPERATION})
	foreach(MODEL ${${OPERATION}_MODELS_LIST})
      foreach(D_DIMENSIONS RANGE 1 ${${OPERATION}_${MODEL}_MAX_D_DIMENSIONS})
	    foreach(LEFT_GRADE RANGE 0 ${D_DIMENSIONS})
		  foreach(RIGHT_GRADE RANGE 0 ${D_DIMENSIONS})
            message(STATUS "      - " ${MODEL} ", D = " ${D_DIMENSIONS} ", LEFT_GRADE = " ${LEFT_GRADE} ", RIGHT_GRADE = " ${RIGHT_GRADE})
            set(TARGET_NAME GABenchmark_${OPERATION}_${MODEL}_D${D_DIMENSIONS}_LEFTGRADE${LEFT_GRADE}_RIGHTGRADE${RIGHT_GRADE}_${LIBRARY})
            set(BENCHMARK_EXEC GABenchmark_${OPERATION}_${MODEL}_D${D_DIMENSIONS}_LEFTGRADE${LEFT_GRADE}_RIGHTGRADE${RIGHT_GRADE}_${LIBRARY})
            add_executable(${TARGET_NAME} "${PROJECT_SOURCE_DIR}/${OPERATION}.cpp" "${PROJECT_SOURCE_DIR}/source/${LIBRARY}/Specialized${OPERATION}.cpp")
            set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME ${BENCHMARK_EXEC})
            target_compile_definitions(${TARGET_NAME} PRIVATE
              GABENCHMARK_LIBRARY=${LIBRARY}
		      GABENCHMARK_OPERATION=${OPERATION}
		      GABENCHMARK_MODEL=${MODEL}
		      GABENCHMARK_D_DIMENSIONS=${D_DIMENSIONS}
		      GABENCHMARK_LEFT_GRADE=${LEFT_GRADE}
		      GABENCHMARK_RIGHT_GRADE=${RIGHT_GRADE}
            )
            target_include_directories(${TARGET_NAME} PRIVATE "${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/source/${LIBRARY}" ${${LIBRARY}_INCLUDE_DIR})
            target_link_libraries(${TARGET_NAME} benchmark ${CMAKE_THREAD_LIBS_INIT} ${${LIBRARY}_LIBS_INIT})
            add_test(NAME ${TARGET_NAME} COMMAND ${BENCHMARK_EXEC} --benchmark_format=json --benchmark_out=${BENCHMARK_EXEC}.json)
          endforeach()
        endforeach()
      endforeach()
    endforeach()
  endif()
endforeach()

message(STATUS "")
