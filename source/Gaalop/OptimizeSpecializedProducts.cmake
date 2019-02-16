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

set(ORIGINAL_IN_FILE "${CMAKE_CURRENT_LIST_DIR}/SpecializedProducts.hpg.in")
set(GENERATED_IN_FILE "${Gaalop_OPTIMIZATION_DIR}/SpecializedProducts.hpg.in")
set(GENERATED_HPG_FILE "${Gaalop_OPTIMIZATION_DIR}/SpecializedProducts.hpg")
set(GENERATED_HPP_FILE "${Gaalop_OPTIMIZATION_DIR}/SpecializedProducts.hpp")

include("${CMAKE_CURRENT_LIST_DIR}/SetBasisBlades.cmake")

if(NOT DEFINED BASIS_BLADES_${LEFT_GRADE})
  message(FATAL_ERROR "The BASIS_BLADES_${LEFT_GRADE} variable was not defined.")
endif()
set(LEFT_BASIS_BLADES "${BASIS_BLADES_${LEFT_GRADE}}")

if(NOT DEFINED BASIS_BLADES_${RIGHT_GRADE})
  message(FATAL_ERROR "The BASIS_BLADES_${RIGHT_GRADE} variable was not defined.")
endif()
set(RIGHT_BASIS_BLADES "${BASIS_BLADES_${RIGHT_GRADE}}")

execute_process(COMMAND ${CMAKE_COMMAND} -E compare_files "${ORIGINAL_IN_FILE}" "${GENERATED_IN_FILE}" RESULT_VARIABLE FILES_ARE_DIFFERENT)
if(FILES_ARE_DIFFERENT)
  file(MAKE_DIRECTORY ${Gaalop_OPTIMIZATION_DIR})
  file(COPY "${ORIGINAL_IN_FILE}" DESTINATION ${Gaalop_OPTIMIZATION_DIR})
  configure_file("${GENERATED_IN_FILE}" "${GENERATED_HPG_FILE}" @ONLY)
  get_filename_component(Gaalop_JAR_DIR ${Gaalop_JAR_FILE} DIRECTORY)
  execute_process(COMMAND "${Java_JAVA_EXECUTABLE}" -jar "${Gaalop_JAR_FILE}" -algebraBaseDir "${CMAKE_CURRENT_LIST_DIR}/algebras" -algebraName "${Gaalop_ALGEBRA_NAME}" -m "${MAXIMA_BIN}" -optimizer "de.gaalop.tba.Plugin" -generator "de.gaalop.compressed.Plugin" -i "${GENERATED_HPG_FILE}" -o "${GENERATED_HPP_FILE}" WORKING_DIRECTORY "${Gaalop_JAR_DIR}")
endif()