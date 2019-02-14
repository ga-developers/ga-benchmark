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

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

# Set models and parameters
set(MODELS_LIST
  ConformalModel
  EuclideanModel
  HomogeneousModel
  MinkowskiModel
)

set(ConformalModel_MIN_D_DIMENSIONS 2)
set(ConformalModel_MAX_D_DIMENSIONS 3)

set(EuclideanModel_MIN_D_DIMENSIONS 2)
set(EuclideanModel_MAX_D_DIMENSIONS 5)

set(HomogeneousModel_MIN_D_DIMENSIONS 2)
set(HomogeneousModel_MAX_D_DIMENSIONS 4)

set(MinkowskiModel_MIN_D_DIMENSIONS 2)
set(MinkowskiModel_MAX_D_DIMENSIONS 3)

# Find tested libraries
subdirlist(LIBRARIES_LIST "${PROJECT_SOURCE_DIR}/source")

message(STATUS "")
message(STATUS "Detected geometric algebra libraries and library generators:")
foreach(LIBRARY ${LIBRARIES_LIST})
  if(EXISTS "${PROJECT_SOURCE_DIR}/source/${LIBRARY}/CMakeLists.txt")
    include("${PROJECT_SOURCE_DIR}/source/${LIBRARY}/CMakeLists.txt")
    if(${${LIBRARY}_ENABLED})
      message(STATUS "  - " ${LIBRARY} " (enabled)")
    else()
      message(STATUS "  - " ${LIBRARY} " (disabled or not detected)")
    endif()
  endif()
endforeach()

# Create benchmarks...
message(STATUS "")
message(STATUS "Benchmarks:")

# ... for products
set(OPERATION Products)

foreach(LIBRARY ${LIBRARIES_LIST})
  if(${${LIBRARY}_ENABLED})
    message(STATUS "")
    message(STATUS "  - " ${LIBRARY})
    message(STATUS "    - " ${OPERATION})
    foreach(MODEL ${MODELS_LIST})
      foreach(D_DIMENSIONS RANGE ${${MODEL}_MIN_D_DIMENSIONS} ${${MODEL}_MAX_D_DIMENSIONS})
        foreach(LEFT_GRADE RANGE 0 ${D_DIMENSIONS})
          foreach(RIGHT_GRADE RANGE 0 ${D_DIMENSIONS})
            message(STATUS "      - " ${MODEL} ", D = " ${D_DIMENSIONS} ", LEFT_GRADE = " ${LEFT_GRADE} ", RIGHT_GRADE = " ${RIGHT_GRADE})
              
            set(TARGET_NAME GABenchmark_${OPERATION}_${MODEL}_D${D_DIMENSIONS}_LEFTGRADE${LEFT_GRADE}_RIGHTGRADE${RIGHT_GRADE}_${LIBRARY})
            add_executable(${TARGET_NAME} "${PROJECT_SOURCE_DIR}/${OPERATION}.cpp")

            set(BENCHMARK_EXEC GABenchmark_${OPERATION}_${MODEL}_D${D_DIMENSIONS}_LEFTGRADE${LEFT_GRADE}_RIGHTGRADE${RIGHT_GRADE}_${LIBRARY})
            set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME ${BENCHMARK_EXEC})
              
            target_compile_definitions(${TARGET_NAME} PRIVATE
              GABENCHMARK_LIBRARY=${LIBRARY}
              GABENCHMARK_OPERATION=${OPERATION}
              GABENCHMARK_MODEL=${MODEL}
              GABENCHMARK_D_DIMENSIONS=${D_DIMENSIONS}
              GABENCHMARK_LEFT_GRADE=${LEFT_GRADE}
              GABENCHMARK_RIGHT_GRADE=${RIGHT_GRADE}
            )

            string(CONFIGURE "${${LIBRARY}_Products_INCLUDE_DIR}" Products_INCLUDE_DIR)
            target_include_directories(${TARGET_NAME} PRIVATE "${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/source/${LIBRARY}" ${${LIBRARY}_INCLUDE_EXTRA_DIR} ${${LIBRARY}_INCLUDE_DIR} ${Products_INCLUDE_DIR})
              
            string(CONFIGURE "${${LIBRARY}_Products_LIBS_INIT}" Products_LIBS_INIT)
            target_link_libraries(${TARGET_NAME} benchmark ${CMAKE_THREAD_LIBS_INIT} ${${LIBRARY}_LIBS_INIT} ${Products_LIBS_INIT})
              
            if(${LIBRARY}_Products_PRE_BUILD_COMMANDS)
              string(CONFIGURE "${${LIBRARY}_Products_PRE_BUILD_COMMANDS}" Products_CUSTOM_COMMANDS)
              add_custom_target(${TARGET_NAME}_PRE_BUILD ${Products_CUSTOM_COMMANDS})
              add_dependencies(${TARGET_NAME} ${TARGET_NAME}_PRE_BUILD)
            endif()

            if(${LIBRARY}_Products_PRE_LINK_COMMANDS)
              string(CONFIGURE "${${LIBRARY}_Products_PRE_LINK_COMMANDS}" Products_CUSTOM_COMMANDS)
              add_custom_command(TARGET ${TARGET_NAME} PRE_LINK ${Products_CUSTOM_COMMANDS})
            endif()

            if(${LIBRARY}_Products_POST_BUILD_COMMANDS)
              string(CONFIGURE "${${LIBRARY}_Products_POST_BUILD_COMMANDS}" Products_CUSTOM_COMMANDS)
              add_custom_command(TARGET ${TARGET_NAME} POST_BUILD ${Products_CUSTOM_COMMANDS})
            endif()

            add_test(NAME ${TARGET_NAME} COMMAND ${BENCHMARK_EXEC} --benchmark_format=json --benchmark_out=${BENCHMARK_EXEC}.json)

          endforeach()
        endforeach()
      endforeach()
    endforeach()
  endif()
endforeach()

message(STATUS "")