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

if(NOT DEFINED MODEL)
  message(FATAL_ERROR "The MODEL variable was not defined.")
endif()

if(NOT DEFINED D_DIMENSIONS)
  message(FATAL_ERROR "The D_DIMENSIONS variable was not defined.")
endif()

if(MODEL STREQUAL "ConformalModel")

  if(D_DIMENSIONS EQUAL 2)

    set(BASIS_BLADES_0 "1")
    set(BASIS_BLADES_1 "e1, e2, eo, ei")
    set(BASIS_BLADES_2 "e1^e2, e1^eo, e1^ei, e2^eo, e2^ei, eo^ei")
    set(BASIS_BLADES_3 "e1^e2^eo, e1^e2^ei, e1^eo^ei, e2^eo^ei")
    set(BASIS_BLADES_4 "e1^e2^eo^ei")

  elseif(D_DIMENSIONS EQUAL 3)

    set(BASIS_BLADES_0 "1")
    set(BASIS_BLADES_1 "e1, e2, e3, eo, ei")
    set(BASIS_BLADES_2 "e1^e2, e1^e3, e1^eo, e1^ei, e2^e3, e2^eo, e2^ei, e3^eo, e3^ei, eo^ei")
    set(BASIS_BLADES_3 "e1^e2^e3, e1^e2^eo, e1^e2^ei, e1^e3^eo, e1^e3^ei, e1^eo^ei, e2^e3^eo, e2^e3^ei, e2^eo^ei, e3^eo^ei")
    set(BASIS_BLADES_4 "e1^e2^e3^eo, e1^e2^e3^ei, e1^e2^eo^ei, e1^e3^eo^ei, e2^e3^eo^ei")
    set(BASIS_BLADES_5 "e1^e2^e3^eo^ei")

  endif()

elseif(MODEL STREQUAL "EuclideanModel")

  if(D_DIMENSIONS EQUAL 2)

    set(BASIS_BLADES_0 "1")
    set(BASIS_BLADES_1 "e1, e2")
    set(BASIS_BLADES_2 "e1^e2")

  elseif(D_DIMENSIONS EQUAL 3)

    set(BASIS_BLADES_0 "1")
    set(BASIS_BLADES_1 "e1, e2, e3")
    set(BASIS_BLADES_2 "e1^e2, e1^e3, e2^e3")
    set(BASIS_BLADES_3 "e1^e2^e3")

  elseif(D_DIMENSIONS EQUAL 4)

    set(BASIS_BLADES_0 "1")
    set(BASIS_BLADES_1 "e1, e2, e3, e4")
    set(BASIS_BLADES_2 "e1^e2, e1^e3, e1^e4, e2^e3, e2^e4, e3^e4")
    set(BASIS_BLADES_3 "e1^e2^e3, e1^e2^e4, e1^e3^e4, e2^e3^e4")
    set(BASIS_BLADES_4 "e1^e2^e3^e4")

  elseif(D_DIMENSIONS EQUAL 5)

    set(BASIS_BLADES_0 "1")
    set(BASIS_BLADES_1 "e1, e2, e3, e4, e5")
    set(BASIS_BLADES_2 "e1^e2, e1^e3, e1^e4, e1^e5, e2^e3, e2^e4, e2^e5, e3^e4, e3^e5, e4^e5")
    set(BASIS_BLADES_3 "e1^e2^e3, e1^e2^e4, e1^e2^e5, e1^e3^e4, e1^e3^e5, e1^e4^e5, e2^e3^e4, e2^e3^e5, e2^e4^e5, e3^e4^e5")
    set(BASIS_BLADES_4 "e1^e2^e3^e4, e1^e2^e3^e5, e1^e2^e4^e5, e1^e3^e4^e5, e2^e3^e4^e5")
    set(BASIS_BLADES_5 "e1^e2^e3^e4^e5")

  endif()

elseif(MODEL STREQUAL "HomogeneousModel")

  if(D_DIMENSIONS EQUAL 2)

    set(BASIS_BLADES_0 "1")
    set(BASIS_BLADES_1 "e1, e2, ep")
    set(BASIS_BLADES_2 "e1^e2, e1^ep, e2^ep")
    set(BASIS_BLADES_3 "e1^e2^ep")

  elseif(D_DIMENSIONS EQUAL 3)

    set(BASIS_BLADES_0 "1")
    set(BASIS_BLADES_1 "e1, e2, e3, ep")
    set(BASIS_BLADES_2 "e1^e2, e1^e3, e1^ep, e2^e3, e2^ep, e3^ep")
    set(BASIS_BLADES_3 "e1^e2^e3, e1^e2^ep, e1^e3^ep, e2^e3^ep")
    set(BASIS_BLADES_4 "e1^e2^e3^ep")

  elseif(D_DIMENSIONS EQUAL 4)

    set(BASIS_BLADES_0 "1")
    set(BASIS_BLADES_1 "e1, e2, e3, e4, ep")
    set(BASIS_BLADES_2 "e1^e2, e1^e3, e1^e4, e1^ep, e2^e3, e2^e4, e2^ep, e3^e4, e3^ep, e4^ep")
    set(BASIS_BLADES_3 "e1^e2^e3, e1^e2^e4, e1^e2^ep, e1^e3^e4, e1^e3^ep, e1^e4^ep, e2^e3^e4, e2^e3^ep, e2^e4^ep, e3^e4^ep")
    set(BASIS_BLADES_4 "e1^e2^e3^e4, e1^e2^e3^ep, e1^e2^e4^ep, e1^e3^e4^ep, e2^e3^e4^ep")
    set(BASIS_BLADES_5 "e1^e2^e3^e4^ep")

  endif()

elseif(MODEL STREQUAL "MinkowskiModel")

  if(D_DIMENSIONS EQUAL 2)

    set(BASIS_BLADES_0 "1")
    set(BASIS_BLADES_1 "e1, e2, ep, em")
    set(BASIS_BLADES_2 "e1^e2, e1^ep, e1^em, e2^ep, e2^em, ep^em")
    set(BASIS_BLADES_3 "e1^e2^ep, e1^e2^em, e1^ep^em, e2^ep^em")
    set(BASIS_BLADES_4 "e1^e2^ep^em")

  elseif(D_DIMENSIONS EQUAL 3)

    set(BASIS_BLADES_0 "1")
    set(BASIS_BLADES_1 "e1, e2, e3, ep, em")
    set(BASIS_BLADES_2 "e1^e2, e1^e3, e1^ep, e1^em, e2^e3, e2^ep, e2^em, e3^ep, e3^em, ep^em")
    set(BASIS_BLADES_3 "e1^e2^e3, e1^e2^ep, e1^e2^em, e1^e3^ep, e1^e3^em, e1^ep^em, e2^e3^ep, e2^e3^em, e2^ep^em, e3^ep^em")
    set(BASIS_BLADES_4 "e1^e2^e3^ep, e1^e2^e3^em, e1^e2^ep^em, e1^e3^ep^em, e2^e3^ep^em")
    set(BASIS_BLADES_5 "e1^e2^e3^ep^em")

  endif()

endif()