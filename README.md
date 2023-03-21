# heatTransferSim
heatTransferSim is just as the name describes. It is a simulation of heat being distributed throughout a matrix using a
transfer rate of **k**.

## Installation
Just clone this repository with the submodules.

```
git clone --recurse-submodules https://github.com/Rbbingham/heatTransferSim.git
```

## Usage
Build the project using cmake and make. Be sure to specify the PATH to the g++ compiler down below.

```
mkdir build
cd build
cmake -D CMAKE_CXX_COMPILER=<path/to/g++> ..
make
make test
```

## License
[MIT](https://github.com/Rbbingham/heatTransferSim/blob/main/LICENSE.txt)