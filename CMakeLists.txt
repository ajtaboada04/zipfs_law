# Every CMake project needs to start with these two lines
cmake_minimum_required(VERSION 3.20) # This is the minimum version of CMake required
project(Homework VERSION 1.0) # This is the name of the project and its version

set(CMAKE_CXX_STANDARD 20) # This sets the C++ standard to C++20
set(CMAKE_CXX_STANDARD_REQUIRED True) # This tells CMake that the standard must be available

# This line tells CMake to generate the compile_commands.json file, which VSCode can use to provide intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# We place the executables in the bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# We place the libraries in the lib directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include the directory containing zipfs.h
include_directories(${CMAKE_SOURCE_DIR}/include)

# We normally have a CMakeLists.txt file in each directory that has something that needs to be built
add_subdirectory(src)
enable_testing() # This line allows to call ctest after compilation
add_subdirectory(tests)
add_subdirectory(docs)

# Ensure Python is available
find_package(Python3 COMPONENTS Interpreter REQUIRED)

# Path to the Python script
set(PLOT_SCRIPT ${CMAKE_SOURCE_DIR}/scripts/plot_zipf.py)

# Target to generate output.txt from the main executable
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/output.txt
    COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/MyVeryCoolProject > ${CMAKE_BINARY_DIR}/output.txt
    COMMENT "Running MyVeryCoolProject to generate output.txt"
)

# Target to run the Python plot script
add_custom_target(plot_zipf
    DEPENDS ${CMAKE_BINARY_DIR}/output.txt
    COMMAND ${Python3_EXECUTABLE} ${PLOT_SCRIPT} ${CMAKE_BINARY_DIR}/output.txt
    COMMENT "Generating log-log plot using Python script"
)

message(STATUS "To run the plot script after building, use: make plot_zipf")
