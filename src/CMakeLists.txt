set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/homework)

# Collect all .cpp files in the homework directory
file(GLOB SOURCES "*.cpp")

# Iterate over each source file and create an executable
foreach(SOURCE ${SOURCES})
    # Get the base name of the file without extension
    get_filename_component(EXEC_NAME ${SOURCE} NAME_WE)
    
    # Add an executable target
    add_executable(${EXEC_NAME} ${SOURCE})
endforeach()