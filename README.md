# ga-benchmark

## Overview
This repository is a joint effort to define standards and methodologies for benchmarking Geometric Algebra libraries.

The goal of this project is to help physicists, chemists, engineers, and computer scientists to choose the Geometric Algebra library that best suits their practical needs, as well as to push further the improvement of the compared solutions and to motivate the development of new tools.


## Requirements
Make sure that you have all the following tools and libraries installed and working before attempting to use **ga-benchmark**.

Required tools:
- Your favorite [C++14](https://en.wikipedia.org/wiki/C%2B%2B14) compiler
- [CMake](https://cmake.org)

Required C++ libraries:
- [Google Benchmark](https://github.com/google/benchmark)
- Threads (pthread library on Linux, shlwapi library on Windows, and kstat library on Solaris)

Expected Geometric Algebra libraries and library generators:
- [Gaalop: Geometic Algebra Algorithms Optimizer](http://www.gaalop.de)
- [Garamon: Geometric Algebra Recursive and Adaptive Monster](https://sourcesup.renater.fr/scm/?group_id=4044)
- [GATL: Geometric Algebra Template Library](https://github.com/laffernandes/gatl)
- [GluCat: Clifford Algebra Templates](https://github.com/penguian/glucat)
- [Versor](http://versor.mat.ucsb.edu)

Actually, you have to install only the libraries and library generators that you want to test. **ga-benchmark** already provides support for those listed above. The *Further Knowledge* section describes how to include or remove an existing library from the process, and how to include a custom library on it.


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
If your system does not include the expected libraries and library generators listed above then you must install them following the instructions provided by the developers.

The commands below summarize the installation process for each of the expected tools. However, it is important to note that the process may have changed with the release of new versions.

Here, we assume that `ga-benchmark` is the current folder and Linux operating system.

### Gaalop
```bash
$ sudo apt install maven
$ git clone https://github.com/CallForSanity/Gaalop.git libs/gaalop
$ cd libs/gaalop
$ mvn clean package assembly:directory
$ cd ../..
```

### Garamon
```bash
$ sudo apt install libeigen3-dev
$ git clone https://git.renater.fr/garamon.git libs/garamon
$ mkdir libs/garamon/build
$ cd libs/garamon/build
$ cmake ..
$ make
$ for model in e3ga e7ga c2ga c3ga c4ga c5ga c6ga c7ga
  do
    ./garamon_generator ../conf/$model.conf
    cd output/garamon_$model
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make
    cd ../../..
  done
$ cd ../../..
```

### GATL
```bash
$ git clone https://github.com/laffernandes/gatl.git libs/gatl
```

### GluCat
```bash
$ git clone https://github.com/penguian/glucat.git libs/glucat
$ cd libs/glucat
$ make -f admin/Makefile.common cvs
$ ./configure
$ make
$ sudo make install
$ cd ../..
```

### Versor
```bash
$ git clone https://github.com/wolftype/versor.git libs/versor
$ cd libs/versor
$ ./build.sh --math
$ cd ../..
```

### Custom Library
Coming soon.