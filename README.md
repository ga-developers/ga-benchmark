# ga-benchmark

This repository is a joint effort to define standards and methodologies for benchmarking Geometric Algebra libraries, library generators, and code optimizers.

The goal of this project is to help physicists, chemists, engineers, and computer scientists to choose the Geometric Algebra solution that best suits their practical needs, as well as to push further the improvement of the compared solutions and to motivate the development of new tools.

**Contents:**

1. [Requirements](#1-requirements)
2. [Building and Running](#2-building-and-running)
3. [Ploting Results](#3-ploting-results)
4. [Latest Results](#4-latest-results)
5. [Further Knowledge](#5-further-knowledge)
   - [Gaalet](#gaalet)
   - [Gaalop](#gaalop)
   - [Garamon](#garamon)
   - [GATL](#gatl)
   - [GluCat](#glucat)
   - [TbGAL](#tbgal)
   - [Versor](#versor)
   - [How ga-benchmark Recognizes a Solution](#how-ga-benchmark-recognizes-a-solution)
6. [License](#6-license)

## 1. Requirements

Make sure that you have all the following tools, libraries, library generators, and code optimizers installed and working before attempting to use **ga-benchmark**.

Required tools:

- Your favorite [C++17](https://en.wikipedia.org/wiki/C%2B%2B17) compiler
- [CMake](https://cmake.org)
- [Python 3](https://www.python.org) interpreter
- [Jupyter Notebook](https://jupyter.org)

Required C++ libraries:

- [Google Benchmark](https://github.com/google/benchmark)
- Threads (`pthread` library on Linux, `shlwapi` library on Windows, and `kstat` library on Solaris)

Required Python modules:

- `argparse`
- `ipywidgets`
- `json`
- `scipy`
- `shutil`
- `tqdm`
- `typing`

Expected Geometric Algebra libraries, library generators, and code optimizers:

- [Gaalet: Geometric Algebra ALgorithms Expression Templates](https://sourceforge.net/projects/gaalet)
- [Gaalop: Geometic Algebra Algorithms Optimizer](http://www.gaalop.de)
- [Garamon: Geometric Algebra Recursive and Adaptive Monster](https://github.com/vincentnozick/garamon)
- [GATL: Geometric Algebra Template Library](https://github.com/laffernandes/gatl)
- [GluCat: Clifford Algebra Templates](https://github.com/penguian/glucat)
- [TbGAL: Tensor-based Geometric Algebra Library](https://github.com/Prograf-UFF/tbgal)
- [Versor](http://versor.mat.ucsb.edu)

The [Further Knowledge](#6-further-knowledge) section describes how to install the expected libraries, library generators, and code optimizers, and how to make **ga-benchmark** recognize the existence of a solution to be compared, including custom ones not listed above. Notice that Gaalop and Garamon must be instrumented.

## 2. Building and Running

Use the [git clone](https://git-scm.com/docs/git-clone) command to download the project:

```bash
git clone https://github.com/ga-developers/ga-benchmark.git ga-benchmark
cd ga-benchmark
```

The basic steps for configuring and building **ga-benchmark** look like this:

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --parallel 8
```

Call the `test` target to run the benchmark:

```bash
cmake --build . --target test
```

Building and running **ga-benchmark** may take several hours. Please be patient and keep the computer allocated exclusively for the execution of the tests.

## 3. Ploting Results

After running **ga-benchmark**, use the Jupyter Notebook [`ga-benchmark/gabm_results.ipynb`](gabm_results.ipynb) to see tables and charts that compare solutions. Those tables and charts are produced by functions defined in the [`ga-benchmark/gabm.py`](gabm.py) file.

Alternatively, you can generate the tables and charts from the command line. Assuming that the current folder is `ga-benchmark/build` and you want to save resulting charts and tables to the `ga-benchmark/results` folder, call:

```bash
cd ..
python -m gabm -i ./build -o ./results
```

If everything is alright, then results are in the `ga-benchmark/results` folder. This is the folder structure expected by the repository [`https://github.com/ga-developers/ga-benchmark-runs`](https://github.com/ga-developers/ga-benchmark-runs), since it also includes a copy of the input JSON files.

## 4. Latest Results

The latest results are available here: [`https://github.com/ga-developers/ga-benchmark-runs`](https://github.com/ga-developers/ga-benchmark-runs). Please, help us to keep it updated.

## 5. Further Knowledge

If your system does not include the expected libraries, library generators, and code optimizers listed above, then you must install them following the instructions provided by the developers.

The commands below summarize the installation process of each of the expected solutions. However, one should note that the process may have changed with the release of new versions.

Here, we assume that `ga-benchmark` is the current folder and Linux operating system. The installation procedures will place the expected solutions inside the `ga-benchmark/libs` folder.

### Gaalet

```bash
svn checkout https://svn.code.sf.net/p/gaalet/code/trunk libs/Gaalet/repository
mkdir -p libs/Gaalet/install/include/gaalet
cp libs/Gaalet/repository/include/cpp0x/* libs/Gaalet/install/include/gaalet
```

### Gaalop

```bash
sudo apt install xmaxima
sudo apt install default-jre
mkdir -p libs/Gaalop/download
wget -O libs/Gaalop/download/GaalopPrecompiler.tar.gz "http://www.gaalop.de/wp-content/uploads/x86-64/GaalopPrecompiler-2.0.1447-Linux.tar.gz"
tar xf libs/Gaalop/download/GaalopPrecompiler.tar.gz -C libs/Gaalop/download
mkdir -p libs/Gaalop/install/usr/local/bin/GaalopPrecompiler
mv libs/Gaalop/download/GaalopPrecompiler-2.0.1447-Linux/* libs/Gaalop/install/usr/local/bin/GaalopPrecompiler
rmdir libs/Gaalop/download/GaalopPrecompiler-2.0.1447-Linux
```

See [Gaalop's download page](http://www.gaalop.de/download/) for a list of prebuilt binaries of the precompiler for Linux and Windows.

### Garamon

```bash
sudo apt install libeigen3-dev
git clone https://github.com/vincentnozick/garamon.git libs/Garamon/repository
mkdir libs/Garamon/repository/build
mkdir libs/Garamon/install
cd libs/Garamon/repository/build
cmake ..
make
for conf in ../../../../source/Garamon/algebras/*.conf
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
cd ../../../..
```

### GATL

```bash
git clone https://github.com/laffernandes/gatl.git libs/GATL/repository
mkdir libs/GATL/repository/cpp/build
mkdir libs/GATL/install
cd libs/GATL/repository/cpp/build
cmake -DCMAKE_INSTALL_PREFIX="$(cd ../../../install; pwd -P)" ..
cd ../../../../..
```

### GluCat

```bash
sudo apt install libeigen3-dev
sudo apt install libboost-all-dev
git clone https://github.com/penguian/glucat.git libs/GluCat/repository
cd libs/GluCat/repository
make -f admin/Makefile.common cvs
./configure --disable-pyclical
make
make DESTDIR=$(realpath ../install) install
cd ../../..
```

### TbGAL

```bash
sudo apt install libeigen3-dev
git clone https://github.com/Prograf-UFF/TbGAL.git libs/TbGAL/repository
mkdir libs/TbGAL/repository/build
mkdir libs/TbGAL/install
cd libs/TbGAL/repository/build
cmake -DCMAKE_INSTALL_PREFIX="$(cd ../../install; pwd -P)" ..
cd ../../../..
```

### Versor

```bash
git clone https://github.com/wolftype/versor.git libs/Versor/repository
mkdir libs/Versor/repository/build
mkdir libs/Versor/install
cd libs/Versor/repository/build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
make DESTDIR=../../install install
cd ../../../..
```

### How **ga-benchmark** Recognizes a Solution

A given libraries, library generators, and code optimizers will be recognized by **ga-benchmark** if and only if the `ga-benchmark/source` folder includes a subfolder with the benchmark code of the given solution. The [`ga-benchmark/source/README.md`](source/README.md) file presents detailed instructions about how to prepare such subfolder.

## 6. License

This software is licensed under the GNU General Public License v3.0. See the [`LICENSE`](LICENSE) file for details.
