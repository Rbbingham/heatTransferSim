cmake_minimum_required(VERSION 3.24)

# set project name
project(heatTransferSim C CXX)

find_package(OpenMP)
if(OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fopenmp")

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

# add the directories for the build
add_subdirectory("src")
add_subdirectory("lib/googletest")
add_subdirectory("test")

enable_testing()