cmake_minimum_required(VERSION 3.14)
project(Small-Infer)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SPDLOG_INC ${PROJECT_SOURCE_DIR}/3rdparty/spdlog/include/)
set(SINFER_INC ${PROJECT_SOURCE_DIR}/include/)

aux_source_directory(./src/data DIR_DATA)

add_library(sinfer SHARED ${SINFER_INC} ${DIR_DATA})

#Unit test
add_subdirectory(${PROJECT_SOURCE_DIR}/3rdparty/googletest)
enable_testing()

target_include_directories(sinfer PUBLIC ${gtest_SOURCE_DIR}/include)
target_include_directories(sinfer PUBLIC ${SPDLOG_INC})

# test
add_subdirectory(test)
