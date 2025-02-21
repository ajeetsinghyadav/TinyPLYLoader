# TinyPLYLoader
A simple C++ project to load and parse .PLY files using TinyPly.

## Features
Loads .PLY mesh files.

* Extracts vertices, faces, and scalar values (vertex_scalar, face_scalar).
* Uses TinyPly as a Git submodule.
* Supports C++17 and CMake for easy compilation.

## Clone the Repository & Add TinyPly Submodule

```
git clone https://github.com/YOUR_GITHUB_USERNAME/TinyPLYLoader.git
cd TinyPLYLoader

# Initialize and update the submodule
git submodule add https://github.com/ddiakopoulos/tinyply.git 3rd_party/tinyply
git submodule update --init --recursive
```

## Build the Project with CMake

```
rm -rf build
mkdir build && cd build
cmake ..
make
```

## Run the PLY Loader
```
./LoadPLY
```