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

#if GABENCHMARK_CHECK_MODEL(ConformalModel)

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

#elif GABENCHMARK_CHECK_MODEL(EuclideanModel)

    #if GABENCHMARK_D_DIMENSIONS == 2
        
        #include <e2ga/Mvec.hpp>
        
        namespace gabenchmark {

            using namespace e2ga;
            
        }

    #elif GABENCHMARK_D_DIMENSIONS == 3
        
        #include <e3ga/Mvec.hpp>
        
        namespace gabenchmark {

            using namespace e3ga;
            
        }

    #elif GABENCHMARK_D_DIMENSIONS == 4
        
        #include <e4ga/Mvec.hpp>
        
        namespace gabenchmark {

            using namespace e4ga;
            
        }

    #elif GABENCHMARK_D_DIMENSIONS == 5
        
        #include <e5ga/Mvec.hpp>
        
        namespace gabenchmark {

            using namespace e5ga;
            
        }

    #endif

#elif GABENCHMARK_CHECK_MODEL(HomogeneousModel)

    #if GABENCHMARK_D_DIMENSIONS == 2
        
        #include <h2ga/Mvec.hpp>
        
        namespace gabenchmark {

            using namespace h2ga;
            
        }

    #elif GABENCHMARK_D_DIMENSIONS == 3
        
        #include <h3ga/Mvec.hpp>
        
        namespace gabenchmark {

            using namespace h3ga;
            
        }

    #elif GABENCHMARK_D_DIMENSIONS == 4
        
        #include <h4ga/Mvec.hpp>
        
        namespace gabenchmark {

            using namespace h4ga;
            
        }

    #endif

#elif GABENCHMARK_CHECK_MODEL(MinkowskiModel)

    #if GABENCHMARK_D_DIMENSIONS == 2
        
        #include <m2ga/Mvec.hpp>
        
        namespace gabenchmark {

            using namespace m2ga;

        }

    #elif GABENCHMARK_D_DIMENSIONS == 3
        
        #include <m3ga/Mvec.hpp>
        
        namespace gabenchmark {

            using namespace m3ga;

        }

    #endif

#endif

#endif // __GABENCHMARK_SPECIALIZED_ALGEBRA_HPP__