# ga-benchmark

Contents:
1. [Overview](#1-overview)
2. [Requirements](#2-requirements)
3. [Building](#3-building)
4. [Compiling and Running](#4-compiling-and-running)
5. [Ploting Results](#5-ploting-results)
6. [Latest Results](#6-latest-results)
7. [Further Knowledge](#7-further-knowledge)
   - [Gaalop](#gaalop)
   - [Garamon](#garamon)
   - [GATL](#gatl)
   - [GluCat](#glucat)
   - [Versor](#versor)
   - [How ga-benchmark Recognizes a Solution](#how-ga-benchmark-recognizes-a-solution)
8. [License](#8-license)


## 1. Overview
This repository is a joint effort to define standards and methodologies for benchmarking Geometric Algebra libraries.

The goal of this project is to help physicists, chemists, engineers, and computer scientists to choose the Geometric Algebra library that best suits their practical needs, as well as to push further the improvement of the compared solutions and to motivate the development of new tools.


## 2. Requirements
Make sure that you have all the following tools, libraries and library generators installed and working before attempting to use **ga-benchmark**.

Required tools:
- Your favorite [C++17](https://en.wikipedia.org/wiki/C%2B%2B14) compiler
- [Python 3](https://www.python.org) interpreter
- [CMake](https://cmake.org)

Required C++ libraries:
- [Google Benchmark](https://github.com/google/benchmark)
- Threads (`pthread` library on Linux, `shlwapi` library on Windows, and `kstat` library on Solaris)

Required Python modules:
- `argparse`
- `json`
- `matplotlib`
- `numpy`
- `typing`

Expected Geometric Algebra libraries and library generators:
- [Gaalop: Geometic Algebra Algorithms Optimizer](http://www.gaalop.de)
- [Garamon: Geometric Algebra Recursive and Adaptive Monster](https://sourcesup.renater.fr/scm/?group_id=4044)
- [GATL: Geometric Algebra Template Library](https://github.com/laffernandes/gatl)
- [GluCat: Clifford Algebra Templates](https://github.com/penguian/glucat)
- [Versor](http://versor.mat.ucsb.edu)

The (Further Knowledge)[#7-further-knowledge] section describes how to install the expected libraries and library generators, and how to make **ga-benchmark** recognize the existence of a solution to be compared, including custom ones not listed above. Notice that Gaalop and Garamon must be instrumented 


## 3. Building
Use the [git clone](https://git-scm.com/docs/git-clone) command to download the project:
```bash
$ git clone https://github.com/ga-developers/ga-benchmark.git ga-benchmark
$ cd ga-benchmark
```

The basic steps for configuring and building **ga-benchmark** look like this in Linux:
```bash
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
```

## 4. Compiling and Running
Assuming a makefile generator was used:
```bash
$ make -j8
$ make test
```

## 5. Ploting Results
Assuming that the current folder is `ga-benchmark/build` and you want to save resulting charts and tables to the `ga-benchmark/results` folder:
```bash
$ cd ..
$ python -m plot -i ./build -o ./results
```

If everything is alright, then results are in the `ga-benchmark/results` folder.


## 6. Latest Results
The latest results are available here: (`ga-benchmark/runs/results-2019.03.23.zip`)[runs/results-2019.03.23.zip]. 


## 7. Further Knowledge
If your system does not include the expected libraries and library generators listed above then you must install them following the instructions provided by the developers.

The commands below summarize the installation process of each of the expected solutions. However, it is important to note that the process may have changed with the release of new versions.

Here, we assume that `ga-benchmark` is the current folder and Linux operating system. The installation procedures will place the expected solutions inside the `ga-benchmark/libs` folder.

### Gaalop
```bash
$ sudo apt install xmaxima
$ sudo apt install default-jre
$ mkdir -p libs/Gaalop/download
$ wget -O libs/Gaalop/download/GaalopPrecompiler.tar.gz "http://www.gaalop.de/wp-content/uploads/x86-64/GaalopPrecompiler-2.0.1447-Linux.tar.gz"
$ tar xf libs/Gaalop/download/GaalopPrecompiler.tar.gz -C libs/Gaalop/download
$ mkdir -p libs/Gaalop/install/usr/local/bin/GaalopPrecompiler
$ mv libs/Gaalop/download/GaalopPrecompiler-2.0.1447-Linux/* libs/Gaalop/install/usr/local/bin/GaalopPrecompiler
$ rmdir libs/Gaalop/download/GaalopPrecompiler-2.0.1447-Linux
```

See [Gaalop's download page](http://www.gaalop.de/download/) for a list of prebuilt binaries of the precompiler for Linux and Windows.

### Garamon
```bash
$ sudo apt install libeigen3-dev
$ git clone https://git.renater.fr/garamon.git libs/Garamon/repository
$ mkdir libs/Garamon/repository/build
$ mkdir libs/Garamon/install
$ cd libs/Garamon/repository/build
$ cmake ..
$ make
$ for conf in ../../../../source/Garamon/algebras/*.conf
  do
    ./garamon_generator $conf
    filename=$(basename -- "$conf")
    cd output/garamon_"${filename%.*}"
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make
    make DESTDIR=../../../../../install install
    cd ../../..
  done
$ cd ../../../..
```

### GATL
```bash
$ git clone https://github.com/laffernandes/gatl.git libs/GATL/repository
```

### GluCat
```bash
$ sudo apt install libeigen3-dev
$ sudo apt install libboost-all-dev
$ git clone https://github.com/penguian/glucat.git libs/GluCat/repository
$ cd libs/GluCat/repository
$ make -f admin/Makefile.common cvs
$ ./configure --disable-pyclical
$ make
$ make DESTDIR=$(realpath ../install) install
$ cd ../../..
```

### Versor
```bash
$ git clone https://github.com/wolftype/versor.git libs/Versor/repository
$ mkdir libs/Versor/repository/build
$ mkdir libs/Versor/install
$ cd libs/Versor/repository/build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make
$ make DESTDIR=../../install install
$ cd ../../../..
```

### How **ga-benchmark** Recognizes a Solution
A given library or library generator will be recognized by **ga-benchmark** if and only if the `ga-benchmark/source` folder includes a subfolder with the benchmark code of the given solution. The [`ga-benchmark/source/README.md`](source/README.md) file presents detailed instructions about how to prepare such subfolder.


## 8. License
This software is licensed under the GNU General Public License v3.0. See the [`LICENSE`](LICENSE) file for details.
