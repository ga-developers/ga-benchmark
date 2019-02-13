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

set(Gaalop_ENABLED true)

find_package(Java COMPONENTS Runtime)
if(NOT ${Java_FOUND})
  message(WARNING "Gaalop requires Java, which was not found.")
  set(Gaalop_ENABLED false)
endif()

find_program(MAXIMA_BIN NAMES "maxima" "maxima.sh" "maxima.bat" CACHE PATH "Maxima binary path.")
if(MAXIMA_BIN-NOTFOUND)
  message(WARNING "Gaalop requires Maxima, which was not found.")
  set(Gaalop_ENABLED false)
endif()

set(Gaalop_ConformalModel_MNEMONIC "c")
set(Gaalop_EuclideanModel_MNEMONIC "e")
set(Gaalop_HomogeneousModel_MNEMONIC "h")
set(Gaalop_MinkowskiModel_MNEMONIC "m")

set(Gaalop_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/Gaalop/install/usr/local/bin/GaalopPrecompiler")

find_path(Gaalop_INCLUDE_DIR NAMES GPCUtils.h HINTS "${Gaalop_ROOT_DIR}/include" DOC "The include directory of the Geometric Algebra Algorithms Optimizer (Gaalop).")
set(Gaalop_INCLUDE_EXTRA_DIR "") # no dependencies

if(NOT EXISTS ${Gaalop_INCLUDE_DIR})
  message(WARNING "The path defined in Gaalop_INCLUDE_DIR doesn't exist.")
  set(Gaalop_ENABLED false)
endif()

find_library(Gaalop_LIBRARY NAMES gpc-base HINTS "${Gaalop_ROOT_DIR}/lib" DOC "The library of the Geometric Algebra Algorithms Optimizer (Gaalop).")

if(NOT EXISTS ${Gaalop_LIBRARY})
  message(WARNING "The path defined in Gaalop_LIBRARY doesn't exist.")
  set(Gaalop_ENABLED false)
endif()

find_file(Gaalop_JAR_FILE NAMES starter-1.0.0.jar HINTS "${Gaalop_ROOT_DIR}/share/gpc/gaalop" DOC "The interpreter of the Geometric Algebra Algorithms Optimizer (Gaalop).")

if(NOT EXISTS ${Gaalop_JAR_FILE})
  message(WARNING "The path defined in Gaalop_JAR_FILE doesn't exist.")
  set(Gaalop_ENABLED false)
endif()

get_filename_component(Gaalop_JAR_DIR ${Gaalop_JAR_FILE} DIRECTORY)

foreach(MODEL ${MODELS_LIST})
  foreach(D_DIMENSIONS RANGE ${${MODEL}_MIN_D_DIMENSIONS} ${${MODEL}_MAX_D_DIMENSIONS})
    set(Gaalop_${MODEL}_D${D_DIMENSIONS}_LIBS_INIT ${Gaalop_LIBRARY})
    
    set(Gaalop_ALGEBRA_NAME ${Gaalop_${MODEL}_MNEMONIC}${D_DIMENSIONS}ga)
    set(Gaalop_ALGEBRA_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source/Gaalop/algebras")

    set(Gaalop_${MODEL}_D${D_DIMENSIONS}_INCLUDE_DIR "")
    set(Gaalop_${MODEL}_D${D_DIMENSIONS}_PRE_BUILD_COMMANDS "")
    file(GLOB Gaalop_SOURCE_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/source/Gaalop" "${CMAKE_CURRENT_SOURCE_DIR}/source/Gaalop/*")
    foreach(Gaalop_SOURCE_FILE ${Gaalop_SOURCE_FILES})
      if(${Gaalop_SOURCE_FILE} MATCHES ".*\\.cpg$")
        get_filename_component(Gaalop_SOURCE_FILENAME ${Gaalop_SOURCE_FILE} NAME_WE)
        set(Gaalop_GENERATED_FILE "${Gaalop_SOURCE_FILENAME}.cpp")
      elseif(${Gaalop_SOURCE_FILE} MATCHES ".*\\.hpg$")
        get_filename_component(Gaalop_SOURCE_FILENAME ${Gaalop_SOURCE_FILE} NAME_WE)
        set(Gaalop_GENERATED_FILE "${Gaalop_SOURCE_FILENAME}.hpp")
      else()
        continue()
      endif()
      list(APPEND Gaalop_${MODEL}_D${D_DIMENSIONS}_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/source/\${TARGET_NAME}")
      list(APPEND Gaalop_${MODEL}_D${D_DIMENSIONS}_PRE_BUILD_COMMANDS COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/source/\${TARGET_NAME}")
      list(APPEND Gaalop_${MODEL}_D${D_DIMENSIONS}_PRE_BUILD_COMMANDS COMMAND "${Java_JAVA_EXECUTABLE}" -jar "${Gaalop_JAR_FILE}" -algebraName "${Gaalop_ALGEBRA_NAME}" -algebraBaseDir "${Gaalop_ALGEBRA_BASE_DIR}" -m "${MAXIMA_BIN}" -optimizer "de.gaalop.tba.Plugin" -generator "de.gaalop.compressed.Plugin" -i "${CMAKE_CURRENT_SOURCE_DIR}/source/Gaalop/${Gaalop_SOURCE_FILE}" -o "${CMAKE_CURRENT_BINARY_DIR}/source/\${TARGET_NAME}/${Gaalop_GENERATED_FILE}" WORKING_DIRECTORY "${Gaalop_JAR_DIR}")
    endforeach()
  endforeach()
endforeach()

set(Gaalop_ENABLED ${Gaalop_ENABLED} CACHE BOOL "If set, the Geometric Algebra Algorithms Optimizer (Gaalop) is added to the benchmark.")