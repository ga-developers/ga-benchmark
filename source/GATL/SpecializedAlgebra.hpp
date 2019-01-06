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
along with GA-Benchmark. If not, see <https://www.gnu.org/licenses/>.
/**/

#ifndef __GABENCHMARK_SPECIALIZED_ALGEBRA_HPP__
#define __GABENCHMARK_SPECIALIZED_ALGEBRA_HPP__

#if GABENCHMARK_CHECK_MODEL(ConformalModel)

    #if GABENCHMARK_D_DIMENSIONS == 2
        
        #include <ga2c.hpp>
        
        namespace gabenchmark {

            using namespace ga2c;

        }

    #elif GABENCHMARK_D_DIMENSIONS == 3
        
        #include <ga3c.hpp>
        
        namespace gabenchmark {

            using namespace ga3c;

        }

    #endif

#elif GABENCHMARK_CHECK_MODEL(EuclideanModel)

    #if GABENCHMARK_D_DIMENSIONS == 2
        
        #include <ga2e.hpp>
        
        namespace gabenchmark {

            using namespace ga2e;
            
        }

    #elif GABENCHMARK_D_DIMENSIONS == 3
        
        #include <ga3e.hpp>
        
        namespace gabenchmark {

            using namespace ga3e;
            
        }

    #elif GABENCHMARK_D_DIMENSIONS == 4
        
        #include <ga4e.hpp>
        
        namespace gabenchmark {

            using namespace ga4e;
            
        }

    #elif GABENCHMARK_D_DIMENSIONS == 5
        
        #include <ga5e.hpp>
        
        namespace gabenchmark {

            using namespace ga5e;
            
        }

    #endif

#elif GABENCHMARK_CHECK_MODEL(HomogeneousModel)

    #if GABENCHMARK_D_DIMENSIONS == 2
        
        #include <ga2h.hpp>
        
        namespace gabenchmark {

            using namespace ga2h;
            
        }

    #elif GABENCHMARK_D_DIMENSIONS == 3
        
        #include <ga3h.hpp>
        
        namespace gabenchmark {

            using namespace ga3h;
            
        }

    #elif GABENCHMARK_D_DIMENSIONS == 4
        
        #include <ga4h.hpp>
        
        namespace gabenchmark {

            using namespace ga4h;
            
        }

    #endif

#elif GABENCHMARK_CHECK_MODEL(MinkowskiModel)

    #if GABENCHMARK_D_DIMENSIONS == 2
        
        #include <ga2m.hpp>
        
        namespace gabenchmark {

            using namespace ga2m;

        }

    #elif GABENCHMARK_D_DIMENSIONS == 3
        
        #include <ga3m.hpp>
        
        namespace gabenchmark {

            using namespace ga3m;

        }

    #endif

#endif

#endif // __GABENCHMARK_SPECIALIZED_ALGEBRA_HPP__
