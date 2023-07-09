cmake_minimum_required(VERSION 3.14)
project(Small-Infer)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Unit test
add_subdirectory(${PROJECT_SOURCE_DIR}/3rdparty/googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


# test
add_subdirectory(test)
