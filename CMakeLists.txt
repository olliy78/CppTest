cmake_minimum_required(VERSION 3.10)
project(cpptest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main executable
add_executable(cpptest src/main.cpp src/operations.cpp)

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test executable
add_executable(cpptest_tests tests/test_operations.cpp src/operations.cpp)
target_link_libraries(cpptest_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(cpptest_tests)
