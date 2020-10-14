cmake_minimum_required(VERSION 3.10)

# Set project name and version
project(gdb-lite VERSION 1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(submodules/libelfin submodules/linenoise include)

file(GLOB gdblite_SRC
    "src/*.cpp"
    "submodules/linenoise/linenoise.c"
)

add_executable(gdblite ${gdblite_SRC})
