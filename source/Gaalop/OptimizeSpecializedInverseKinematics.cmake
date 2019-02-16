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

set(ORIGINAL_HPG_FILE "${CMAKE_CURRENT_LIST_DIR}/SpecializedInverseKinematics.hpg")
set(GENERATED_HPG_FILE "${Gaalop_OPTIMIZATION_DIR}/SpecializedInverseKinematics.hpg")
set(GENERATED_HPP_FILE "${Gaalop_OPTIMIZATION_DIR}/SpecializedInverseKinematics.hpp")

execute_process(COMMAND ${CMAKE_COMMAND} -E compare_files "${ORIGINAL_HPG_FILE}" "${GENERATED_HPG_FILE}" RESULT_VARIABLE FILES_ARE_DIFFERENT)
if(FILES_ARE_DIFFERENT)
  file(MAKE_DIRECTORY ${Gaalop_OPTIMIZATION_DIR})
  file(COPY "${ORIGINAL_HPG_FILE}" DESTINATION ${Gaalop_OPTIMIZATION_DIR})
  get_filename_component(Gaalop_JAR_DIR ${Gaalop_JAR_FILE} DIRECTORY)
  execute_process(COMMAND "${Java_JAVA_EXECUTABLE}" -jar "${Gaalop_JAR_FILE}" -algebraBaseDir "${CMAKE_CURRENT_LIST_DIR}/algebras" -algebraName "${Gaalop_ALGEBRA_NAME}" -m "${MAXIMA_BIN}" -optimizer "de.gaalop.tba.Plugin" -generator "de.gaalop.compressed.Plugin" -i "${GENERATED_HPG_FILE}" -o "${GENERATED_HPP_FILE}" WORKING_DIRECTORY "${Gaalop_JAR_DIR}")
endif()