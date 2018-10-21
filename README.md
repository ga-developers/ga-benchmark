# ga-benchmark

## Overview
This repository is a joint effort to define standards and methodologies for benchmarking Geometric Algebra libraries.

The goal of this project is to help physicists, chemists, engineers and computer scientists to choose the Geometric Algebra library that best suits their practical needs, as well as to push further the improvement of the compared solutions and to motivate the development of new tools.


## Requirements
Make sure that you have all the following tools and libraries installed and working before attempting to use **ga-benchmark**.

Required tools:
- Your favorite [C++11](https://en.wikipedia.org/wiki/C%2B%2B11) compiler
- [Python 3](https://docs.python.org/3)
- [CMake](https://cmake.org)

Required C++ libraries:
- [Google Benchmark](https://github.com/google/benchmark)
- Threads (pthread library on Linux, shlwapi library on Windows, and kstat library on Solaris)

Expectetd Geometric Algebra libraries and library generators:
- [Gaalop: Geometic Algebra Algorithms Optimizer](http://www.gaalop.de)
- [Garamon: Geometric Algebra Recursive and Adaptive Monster](https://sourcesup.renater.fr/scm/?group_id=4044)
- [GATL: Geometric Algebra Template Library](https://github.com/laffernandes/gatl)
- [GluCat: Clifford Algebra Templates](https://github.com/penguian/glucat)
- [Versor](http://versor.mat.ucsb.edu)

*NOTE*: Actually, you have to install only the libraries and library generators that you want to test. **ga-benchmark** already provides support for those listed above. The Further Knowledge section describes how to include or remove an existing library from the process, and how to include a custom library on it.

*NOTE*: The C++ version may change according to the libraries and library generators used in the benchmark.


## Building
Use the [git clone](https://git-scm.com/docs/git-clone) command to download the project:
```bash
$ git clone https://github.com/ga-developers/ga-benchmark.git ga-benchmark
$ cd ga-benchmark
```

The basic steps for configuring and building **ga-benchmark** look like this:
```bash
$ mkdir build
$ cd build

$ cmake [-G <generator>] [options] -DCMAKE_BUILD_TYPE=Release ..
```

## Compiling and Running
Assuming a makefile generator was used:
```bash
$ make
$ make test
```

## Further Knowledge
Coming soon.