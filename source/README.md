# ga-benchmark

## How **ga-benchmark** Recognizes a Solution

Each libraries, library generators, and code optimizers compared by **ga-benchmark** has to be included in `ga-benchmark/source` as a subfolder. The subfolder contains the benchmark code of the compared solutions and must have the following structure:

```plaintext
ga-benchmark/  .................................. The root directory of ga-benchmark.
  source/  ...................................... The directory including the benchmark code of all compared solutions.
    <solution-name>/  ........................... The directory of the benchmark code of a given solution whose name is <solution-name>.
      CMakeLists.txt  ........................... This file declares a set of directives describing the location of the solution.
      SpecializedAlgebra.hpp  ................... This header file configures the expected Geometric Algebra models.
      SpecializedAlgorithm<algorithm-name>.hpp .. Each one of those header files implements an algorithm whose name is <algorithm-name>.
      SpecializedBinaryOperations.hpp  .......... This header file implements the wrapper function for binary operations.
      SpecializedUnaryOperations.hpp  ........... This header file implements the wrapper function for unary operations.
      SpecializedUtils.hpp  ..................... This header file implements functions used by the benchmark's core.
```

Auxiliary files and folders can be included in the `ga-benchmark/source/<solution-name>` subfolder.

The detailed description of the expected content of each source file required by **ga-benchmark** will be included soon.

---
<[Back](../README.md)>
