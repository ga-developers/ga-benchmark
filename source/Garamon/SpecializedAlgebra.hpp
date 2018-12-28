/**
Copyright(C) 2018 ga-developers

Repository: https://github.com/ga-developers/ga-benchmark.git

This file is part of the GA-Benchmark project.

GA-Benchmark is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

GA-Benchmark is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GA-Benchmark. If not, see < https://www.gnu.org/licenses/>.
/**/

#ifndef __GABENCHMARK_SPECIALIZED_ALGEBRA_HPP__
#define __GABENCHMARK_SPECIALIZED_ALGEBRA_HPP__

#if GABENCHMARK_CHECK_MODEL(EuclideanModel)

    #if GABENCHMARK_D_DIMENSIONS == 3
        
        #include <e3ga/Mvec.hpp>
        
        namespace gabenchmark {

            using namespace e3ga;
            
        }

    #endif

#elif GABENCHMARK_CHECK_MODEL(ConformalModel)

    #if GABENCHMARK_D_DIMENSIONS == 2
        
        #include <c2ga/Mvec.hpp>
        
        namespace gabenchmark {

            using namespace c2ga;

        }

    #elif GABENCHMARK_D_DIMENSIONS == 3
        
        #include <c3ga/Mvec.hpp>
        
        namespace gabenchmark {

            using namespace c3ga;

        }

    #endif

#elif GABENCHMARK_CHECK_MODEL(HomogeneousModel)

#elif GABENCHMARK_CHECK_MODEL(MinkowskiModel)

    #if GABENCHMARK_D_DIMENSIONS == 2
        
        #include <st3ga/Mvec.hpp>
        
        namespace gabenchmark {

            using namespace st3ga;

        }

    #endif

#elif GABENCHMARK_CHECK_MODEL(SignedModel)

#endif

#endif // __GABENCHMARK_SPECIALIZED_ALGEBRA_HPP__
