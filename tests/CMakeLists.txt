include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(test_main_zipfs_container  test_main_zipfs_container.cpp)
# Add src as an include so that we can include the header files in the tests
target_include_directories(test_main_zipfs_container PRIVATE ${CMAKE_SOURCE_DIR}/src)
# Link the test executable with the library and GTest
target_link_libraries(
  test_main_zipfs_container
  GTest::gtest_main
)

# Add the test to the test suite
gtest_discover_tests(test_main_zipfs_container)