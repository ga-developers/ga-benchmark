Each library or library generator compared by **ga-benchmark** has to be included in `ga-benchmark/source` as a subfolder. The subfolder contains the benchmark code of the compared solutions and must have the following structure:
```
ga-benchmark/  ................... The root directory of ga-benchmark.
  source/  ....................... The directory including the benchmark code of all compared solutions.
    LibraryName/  ................ The root directory of the benchmark code of a given solution.
      CMakeLists.txt  ............ This file declares a set of directives describing the location of the solution.
      SpecializedAlgebra.hpp  .... This header configures the expected Geometric Algebra models.
      SpecializedProducts.hpp  ... This header implements the wrapper function for products.
      SpecializedUtils.hpp  ...... This header implements functions used by the benchmark's core.
```
Auxiliary files and folders can be included in the subfolder `ga-benchmark/source/LibraryName`.

The detailed description of each source file required by **ga-benchmark** will be included soon.