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

cmake_minimum_required(VERSION 3.10)

if(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
endif()

# Create the project
set(VERSION_MAJOR 2)
set(VERSION_MINOR 0)
set(VERSION_PATCH 2)

project(GA-Benchmark
  VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
  DESCRIPTION "GA-Benchmark is a joint effort to define standards and methodologies for benchmarking Geometric Algebra libraries, library generators, and code optimizers."
  HOMEPAGE_URL https://github.com/ga-developers/ga-benchmark
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)

# Find required packages
find_package(benchmark REQUIRED)
find_package(Threads REQUIRED)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(GoogleBenchmark_EXTRA_LIBRARIES shlwapi) # Google Benchmark needs extra libraries on Windows
endif()

find_path(GoogleBenchmark_INCLUDE_DIR NAMES benchmark/benchmark.h PATHS "${benchmark_DIR}/include" "${benchmark_DIR}/../../../include" DOC "The directory where benchmark includes reside")
set(GoogleBenchmark_INCLUDE_DIRS ${GoogleBenchmark_INCLUDE_DIR})

find_library(GoogleBenchmark_LIBRARY NAMES benchmark PATHS "${benchmark_DIR}/lib" "${benchmark_DIR}/../../../lib" DOC "The benchmark library")
set(GoogleBenchmark_LIBRARIES ${GoogleBenchmark_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${GoogleBenchmark_EXTRA_LIBRARIES})

# Implement some useful macros
macro(subdir_list RESULT PARENTDIR)
  file(GLOB CHILDREN RELATIVE ${PARENTDIR} ${PARENTDIR}/*)
  set(${RESULT} "")
  foreach(CHILD ${CHILDREN})
    if(IS_DIRECTORY ${PARENTDIR}/${CHILD})
      list(APPEND ${RESULT} ${CHILD})
    endif()
  endforeach()
endmacro()

function(configure_target TARGET_NAME OPERATION SOLUTION)
  add_executable(${TARGET_NAME} "${PROJECT_SOURCE_DIR}/${OPERATION}.cpp")
  set_target_properties(${TARGET_NAME} PROPERTIES ${${SOLUTION}_PROPERTIES} OUTPUT_NAME ${TARGET_NAME})
            
  string(CONFIGURE "${${SOLUTION}_${OPERATION}_INCLUDE_DIR}" ${OPERATION}_INCLUDE_DIR)
  target_include_directories(${TARGET_NAME} PRIVATE "${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/source/${SOLUTION}" ${GoogleBenchmark_INCLUDE_DIRS} ${${SOLUTION}_INCLUDE_EXTRA_DIR} ${${SOLUTION}_INCLUDE_DIR} ${${OPERATION}_INCLUDE_DIR})
            
  string(CONFIGURE "${${SOLUTION}_${OPERATION}_LIBS_INIT}" ${OPERATION}_LIBS_INIT)
  target_link_libraries(${TARGET_NAME} ${GoogleBenchmark_LIBRARIES} ${${SOLUTION}_LIBS_INIT} ${${OPERATION}_LIBS_INIT})
            
  if(${SOLUTION}_${OPERATION}_PRE_BUILD_COMMANDS)
    string(CONFIGURE "${${SOLUTION}_${OPERATION}_PRE_BUILD_COMMANDS}" ${OPERATION}_CUSTOM_COMMANDS)
    add_custom_target(${TARGET_NAME}_PRE_BUILD ${${OPERATION}_CUSTOM_COMMANDS})
    add_dependencies(${TARGET_NAME} ${TARGET_NAME}_PRE_BUILD)
  endif()

  if(${SOLUTION}_${OPERATION}_PRE_LINK_COMMANDS)
    string(CONFIGURE "${${SOLUTION}_${OPERATION}_PRE_LINK_COMMANDS}" ${OPERATION}_CUSTOM_COMMANDS)
    add_custom_command(TARGET ${TARGET_NAME} PRE_LINK ${${OPERATION}_CUSTOM_COMMANDS})
  endif()

  if(${SOLUTION}_${OPERATION}_POST_BUILD_COMMANDS)
    string(CONFIGURE "${${SOLUTION}_${OPERATION}_POST_BUILD_COMMANDS}" ${OPERATION}_CUSTOM_COMMANDS)
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD ${${OPERATION}_CUSTOM_COMMANDS})
  endif()

  add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME} --benchmark_format=json --benchmark_out=${TARGET_NAME}.json)
endfunction()

# Set models and parameters
set(MODELS_LIST
  ConformalModel
  EuclideanModel
  HomogeneousModel
  MinkowskiModel
)

set(ConformalModel_ENABLED TRUE)
set(ConformalModel_EXTRA_DIMENSIONS 2)
set(ConformalModel_MIN_D_DIMENSIONS 2)
set(ConformalModel_MAX_D_DIMENSIONS 3)

set(EuclideanModel_ENABLED TRUE)
set(EuclideanModel_EXTRA_DIMENSIONS 0)
set(EuclideanModel_MIN_D_DIMENSIONS 2)
set(EuclideanModel_MAX_D_DIMENSIONS 5)

set(HomogeneousModel_ENABLED FALSE)
set(HomogeneousModel_EXTRA_DIMENSIONS 1)
set(HomogeneousModel_MIN_D_DIMENSIONS 2)
set(HomogeneousModel_MAX_D_DIMENSIONS 4)

set(MinkowskiModel_ENABLED TRUE)
set(MinkowskiModel_EXTRA_DIMENSIONS 2)
set(MinkowskiModel_MIN_D_DIMENSIONS 2)
set(MinkowskiModel_MAX_D_DIMENSIONS 3)

message(STATUS "")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
if(NOT CMAKE_BUILD_TYPE STREQUAL "Release")
  message(STATUS "  ** Warning: Change the build type (CMAKE_BUILD_TYPE) from '${CMAKE_BUILD_TYPE}' to 'Release' for a fair comparison.")
endif()

message(STATUS "")
message(STATUS "Set of models:")
foreach(MODEL ${MODELS_LIST})
  set(GABenchmarkModel_${MODEL}_ENABLED ${${MODEL}_ENABLED} CACHE BOOL "If set, operations of this model are added to the benchmark.")
  if(${GABenchmarkModel_${MODEL}_ENABLED})
    message(STATUS "  - " ${MODEL} " (enabled)")
  else()
    message(STATUS "  - " ${MODEL} " (disabled)")
  endif()
endforeach()

# Find tested libraries, library generators, and code optimizers
subdir_list(SOLUTIONS_LIST "${PROJECT_SOURCE_DIR}/source")

message(STATUS "")
message(STATUS "Detected geometric algebra libraries, library generators, and code optimizers:")
foreach(SOLUTION ${SOLUTIONS_LIST})
  if(EXISTS "${PROJECT_SOURCE_DIR}/source/${SOLUTION}/CMakeLists.txt")
    include("${PROJECT_SOURCE_DIR}/source/${SOLUTION}/CMakeLists.txt")
    if(${${SOLUTION}_ENABLED})
      message(STATUS "  - " ${SOLUTION} " (enabled)")
    else()
      if(${${SOLUTION}_SUCCESS})
        message(STATUS "  - " ${SOLUTION} " (disabled)")
      else()
        message(STATUS "  - " ${SOLUTION} " (not detected)")
      endif()
    endif()
  endif()
endforeach()

# Set operations
set(OPERATIONS_LIST
  AlgorithmInverseKinematics
  BinaryOperations
  UnaryOperations
)

message(STATUS "")
message(STATUS "Set of operations:")
foreach(OPERATION ${OPERATIONS_LIST})
  set(GABenchmarkOperation_${OPERATION}_ENABLED TRUE CACHE BOOL "If set, this kind of operation will be added to the benchmark.")
  if(${GABenchmarkOperation_${OPERATION}_ENABLED})
    message(STATUS "  - " ${OPERATION} " (enabled)")
  else()
    message(STATUS "  - " ${OPERATION} " (disabled)")
  endif()
endforeach()

# Create benchmarks...
message(STATUS "")
message(STATUS "Benchmarks:")

foreach(SOLUTION ${SOLUTIONS_LIST})
  if(${${SOLUTION}_ENABLED})
    message(STATUS "")
    message(STATUS "  - " ${SOLUTION})

    # ... for inverse kinematics
    set(OPERATION AlgorithmInverseKinematics)
    if(GABenchmarkOperation_${OPERATION}_ENABLED)
      set(MODEL ConformalModel)
      if(GABenchmarkModel_${MODEL}_ENABLED)
        set(D_DIMENSIONS 3)

        message(STATUS "    - " ${OPERATION})
        message(STATUS "      - " ${MODEL} ", D = " ${D_DIMENSIONS})
                  
        set(TARGET_NAME GABenchmark_${OPERATION}_${MODEL}_D${D_DIMENSIONS}_${SOLUTION})

        configure_target(${TARGET_NAME} ${OPERATION} ${SOLUTION})

        target_compile_definitions(${TARGET_NAME} PRIVATE
          GABM_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}
          GABM_SYSTEM_VERSION=${CMAKE_SYSTEM_VERSION}
          GABM_COMPILER_ID=${CMAKE_CXX_COMPILER_ID}
          GABM_COMPILER_VERSION=${CMAKE_CXX_COMPILER_VERSION}
          GABM_SOLUTION=${SOLUTION}
          GABM_OPERATION=${OPERATION}
          GABM_MODEL=${MODEL}
          GABM_D_DIMENSIONS=${D_DIMENSIONS}
        )

        set_tests_properties(${TARGET_NAME} PROPERTIES TIMEOUT 300)
      endif()
    endif()

    # ... for binary operations
    set(OPERATION BinaryOperations)
    if(GABenchmarkOperation_${OPERATION}_ENABLED)
      message(STATUS "    - " ${OPERATION})
      foreach(MODEL ${MODELS_LIST})
        if(GABenchmarkModel_${MODEL}_ENABLED)
          foreach(D_DIMENSIONS RANGE ${${MODEL}_MIN_D_DIMENSIONS} ${${MODEL}_MAX_D_DIMENSIONS})
            math(EXPR N_DIMENSIONS "${D_DIMENSIONS} + ${${MODEL}_EXTRA_DIMENSIONS}")
            foreach(LEFT_GRADE RANGE 0 ${N_DIMENSIONS})
              foreach(RIGHT_GRADE RANGE 0 ${N_DIMENSIONS})
                message(STATUS "      - " ${MODEL} ", D = " ${D_DIMENSIONS} ", LEFT_GRADE = " ${LEFT_GRADE} ", RIGHT_GRADE = " ${RIGHT_GRADE})
                  
                set(TARGET_NAME GABenchmark_${OPERATION}_${MODEL}_D${D_DIMENSIONS}_LEFTGRADE${LEFT_GRADE}_RIGHTGRADE${RIGHT_GRADE}_${SOLUTION})

                configure_target(${TARGET_NAME} ${OPERATION} ${SOLUTION})
                
                target_compile_definitions(${TARGET_NAME} PRIVATE
                  GABM_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}
                  GABM_SYSTEM_VERSION=${CMAKE_SYSTEM_VERSION}
                  GABM_COMPILER_ID=${CMAKE_CXX_COMPILER_ID}
                  GABM_COMPILER_VERSION=${CMAKE_CXX_COMPILER_VERSION}
                  GABM_SOLUTION=${SOLUTION}
                  GABM_OPERATION=${OPERATION}
                  GABM_MODEL=${MODEL}
                  GABM_D_DIMENSIONS=${D_DIMENSIONS}
                  GABM_LEFT_GRADE=${LEFT_GRADE}
                  GABM_RIGHT_GRADE=${RIGHT_GRADE}
                )

                set_tests_properties(${TARGET_NAME} PROPERTIES TIMEOUT 300)
              endforeach()
            endforeach()
          endforeach()
        endif()
      endforeach()
    endif()

    # ... for unary operations
    set(OPERATION UnaryOperations)
    if(GABenchmarkOperation_${OPERATION}_ENABLED)
      message(STATUS "    - " ${OPERATION})
      foreach(MODEL ${MODELS_LIST})
        if(GABenchmarkModel_${MODEL}_ENABLED)
          foreach(D_DIMENSIONS RANGE ${${MODEL}_MIN_D_DIMENSIONS} ${${MODEL}_MAX_D_DIMENSIONS})
            math(EXPR N_DIMENSIONS "${D_DIMENSIONS} + ${${MODEL}_EXTRA_DIMENSIONS}")
            foreach(GRADE RANGE 0 ${N_DIMENSIONS})
              message(STATUS "      - " ${MODEL} ", D = " ${D_DIMENSIONS} ", GRADE = " ${GRADE})
                
              set(TARGET_NAME GABenchmark_${OPERATION}_${MODEL}_D${D_DIMENSIONS}_GRADE${GRADE}_${SOLUTION})

              configure_target(${TARGET_NAME} ${OPERATION} ${SOLUTION})
              
              target_compile_definitions(${TARGET_NAME} PRIVATE
                GABM_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}
                GABM_SYSTEM_VERSION=${CMAKE_SYSTEM_VERSION}
                GABM_COMPILER_ID=${CMAKE_CXX_COMPILER_ID}
                GABM_COMPILER_VERSION=${CMAKE_CXX_COMPILER_VERSION}
                GABM_SOLUTION=${SOLUTION}
                GABM_OPERATION=${OPERATION}
                GABM_MODEL=${MODEL}
                GABM_D_DIMENSIONS=${D_DIMENSIONS}
                GABM_GRADE=${GRADE}
              )

              set_tests_properties(${TARGET_NAME} PROPERTIES TIMEOUT 300)
            endforeach()
          endforeach()
        endif()
      endforeach()
    endif()
  endif()
endforeach()

message(STATUS "")