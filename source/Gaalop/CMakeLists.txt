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

set(Gaalop_SUCCESS true)

# Set some constant values
set(Gaalop_ConformalModel_MNEMONIC "c")
set(Gaalop_EuclideanModel_MNEMONIC "e")
set(Gaalop_HomogeneousModel_MNEMONIC "h")
set(Gaalop_MinkowskiModel_MNEMONIC "m")

set(Gaalop_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/Gaalop/install/usr/local/bin/GaalopPrecompiler")

# Find required packages and tools
find_package(Java COMPONENTS Runtime)
if(NOT ${Java_FOUND})
  # message(WARNING "Gaalop requires Java, which was not found.")
  set(Gaalop_SUCCESS false)
endif()

find_program(MAXIMA_BIN NAMES "maxima" "maxima.sh" "maxima.bat" CACHE PATH "Maxima binary path.")
if(MAXIMA_BIN-NOTFOUND)
  # message(WARNING "Gaalop requires Maxima, which was not found.")
  set(Gaalop_SUCCESS false)
endif()

# Find Gaalop library
find_library(Gaalop_LIBRARY NAMES gpc-base HINTS "${Gaalop_ROOT_DIR}/lib" DOC "The library of the Geometric Algebra Algorithms Optimizer (Gaalop).")

if(NOT EXISTS ${Gaalop_LIBRARY})
  # message(WARNING "The path defined in Gaalop_LIBRARY doesn't exist.")
  set(Gaalop_SUCCESS false)
endif()

# Find Gaalop interpreter
find_file(Gaalop_JAR_FILE NAMES starter-1.0.0.jar HINTS "${Gaalop_ROOT_DIR}/share/gpc/gaalop" DOC "The interpreter of the Geometric Algebra Algorithms Optimizer (Gaalop).")

if(NOT EXISTS ${Gaalop_JAR_FILE})
  # message(WARNING "The path defined in Gaalop_JAR_FILE doesn't exist.")
  set(Gaalop_SUCCESS false)
endif()

# Set (global) include directories and libraries
find_path(Gaalop_INCLUDE_DIR NAMES GPCUtils.h HINTS "${Gaalop_ROOT_DIR}/include" DOC "The include directory of the Geometric Algebra Algorithms Optimizer (Gaalop).")
set(Gaalop_INCLUDE_EXTRA_DIR "") # no dependencies

if(NOT EXISTS ${Gaalop_INCLUDE_DIR})
  # message(WARNING "The path defined in Gaalop_INCLUDE_DIR doesn't exist.")
  set(Gaalop_SUCCESS false)
endif()

set(Gaalop_LIBS_INIT ${Gaalop_LIBRARY})

# Set include directories, libraries and pre-build commands for products
set(Gaalop_Products_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/GaalopPrecompiler/\${TARGET_NAME}")
set(Gaalop_Products_LIBS_INIT "")

set(Gaalop_Products_PRE_BUILD_COMMANDS
  COMMAND "${CMAKE_COMMAND}"
    "-DJava_JAVA_EXECUTABLE=\"${Java_JAVA_EXECUTABLE}\""
    "-DMAXIMA_BIN=\"${MAXIMA_BIN}\""
    "-DGaalop_OPTIMIZATION_DIR=\"${CMAKE_CURRENT_BINARY_DIR}/GaalopPrecompiler/\${TARGET_NAME}\""
    "-DGaalop_JAR_FILE=\"${Gaalop_JAR_FILE}\""
    "-DGaalop_ALGEBRA_NAME=\"\${Gaalop_\${MODEL}_MNEMONIC}\${D_DIMENSIONS}ga\""
    "-DMODEL=\${MODEL}"
    "-DD_DIMENSIONS=\${D_DIMENSIONS}"
    -P "${CMAKE_CURRENT_SOURCE_DIR}/source/Gaalop/OptimizeSpecializedUtils.cmake"
  COMMAND "${CMAKE_COMMAND}"
    "-DJava_JAVA_EXECUTABLE=\"${Java_JAVA_EXECUTABLE}\""
    "-DMAXIMA_BIN=\"${MAXIMA_BIN}\""
    "-DGaalop_OPTIMIZATION_DIR=\"${CMAKE_CURRENT_BINARY_DIR}/GaalopPrecompiler/\${TARGET_NAME}\""
    "-DGaalop_JAR_FILE=\"${Gaalop_JAR_FILE}\""
    "-DGaalop_ALGEBRA_NAME=\"\${Gaalop_\${MODEL}_MNEMONIC}\${D_DIMENSIONS}ga\""
    "-DMODEL=\${MODEL}"
    "-DD_DIMENSIONS=\${D_DIMENSIONS}"
    "-DLEFT_GRADE=\${LEFT_GRADE}"
    "-DRIGHT_GRADE=\${RIGHT_GRADE}"
    -P "${CMAKE_CURRENT_SOURCE_DIR}/source/Gaalop/OptimizeSpecializedProducts.cmake"
)

# Set include directories, libraries and pre-build commands for inverse kinematics
set(Gaalop_AlgorithmInverseKinematics_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/GaalopPrecompiler/\${TARGET_NAME}")
set(Gaalop_AlgorithmInverseKinematics_LIBS_INIT "")

set(Gaalop_AlgorithmInverseKinematics_PRE_BUILD_COMMANDS
  COMMAND "${CMAKE_COMMAND}"
    "-DJava_JAVA_EXECUTABLE=\"${Java_JAVA_EXECUTABLE}\""
    "-DMAXIMA_BIN=\"${MAXIMA_BIN}\""
    "-DGaalop_OPTIMIZATION_DIR=\"${CMAKE_CURRENT_BINARY_DIR}/GaalopPrecompiler/\${TARGET_NAME}\""
    "-DGaalop_JAR_FILE=\"${Gaalop_JAR_FILE}\""
    "-DGaalop_ALGEBRA_NAME=\"\${Gaalop_\${MODEL}_MNEMONIC}\${D_DIMENSIONS}ga\""
    "-DMODEL=\${MODEL}"
    "-DD_DIMENSIONS=\${D_DIMENSIONS}"
    -P "${CMAKE_CURRENT_SOURCE_DIR}/source/Gaalop/OptimizeSpecializedUtils.cmake"
  COMMAND "${CMAKE_COMMAND}"
    "-DJava_JAVA_EXECUTABLE=\"${Java_JAVA_EXECUTABLE}\""
    "-DMAXIMA_BIN=\"${MAXIMA_BIN}\""
    "-DGaalop_OPTIMIZATION_DIR=\"${CMAKE_CURRENT_BINARY_DIR}/GaalopPrecompiler/\${TARGET_NAME}\""
    "-DGaalop_JAR_FILE=\"${Gaalop_JAR_FILE}\""
    "-DGaalop_ALGEBRA_NAME=\"\${Gaalop_\${MODEL}_MNEMONIC}\${D_DIMENSIONS}ga\""
    -P "${CMAKE_CURRENT_SOURCE_DIR}/source/Gaalop/OptimizeSpecializedAlgorithmInverseKinematics.cmake"
)

# Job done!
if(${Gaalop_SUCCESS})
  set(Gaalop_ENABLED true CACHE BOOL "If set, the Geometric Algebra Algorithms Optimizer (Gaalop) is added to the benchmark.")
else()
  set(Gaalop_ENABLED false CACHE BOOL "If set, the Geometric Algebra Algorithms Optimizer (Gaalop) is added to the benchmark." FORCE)
endif()