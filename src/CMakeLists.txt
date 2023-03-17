# searches all files ending in .cpp
file(GLOB SOURCES "*.cpp")

# include headers
include_directories(${heatTransferSim_SOURCE_DIR}/include)

# create library for tests
add_library(utils ${SOURCES})

# create executable for our program
add_executable(heatTransferSim ${SOURCES})

# link the libraries
target_link_libraries(utils Test)