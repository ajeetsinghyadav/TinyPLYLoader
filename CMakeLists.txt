cmake_minimum_required(VERSION 3.15)
project(TinyPlyLoader)

set(CMAKE_CXX_STANDARD 17)

# Add TinyPly source files as a library
add_library(tinyply STATIC 3rd_party/tinyply/source/tinyply.cpp)

# Include TinyPly headers
target_include_directories(tinyply PUBLIC 3rd_party/tinyply/source)

# Add executable
add_executable(LoadPLY src/main.cpp src/ply_loader.cpp)

# Link TinyPly to LoadPLY
target_link_libraries(LoadPLY PRIVATE tinyply)
