cmake_minimum_required(VERSION 3.24)

# set project name
project(heatTransferSim C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

# add the directories for the build
add_subdirectory("src")
add_subdirectory("lib/googletest")
add_subdirectory("test")

enable_testing()