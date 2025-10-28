# Rupa Parichay

Pattern recognition using simple Neural Networks

## Build Instructions

This project uses [CMake](https://cmake.org) for cross platform builds.

#### Example - Linux with Unix Makefiles release build

```sh 
mkdir build && cd build
cmake .. -G"Unix Makefiles"
make -j$(nproc)
```

This will build the executable `rupa-parichay` at the root of `build` directory.
