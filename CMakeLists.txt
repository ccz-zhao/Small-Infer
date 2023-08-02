cmake_minimum_required(VERSION 3.14)
project(Small-Infer)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SINFER_ROOT_DIR ${CMAKE_SOURCE_DIR})
set(SINFER_INC ${SINFER_ROOT_DIR}/include)
set(SPDLOG_INC ${SINFER_ROOT_DIR}/3rdparty/spdlog/include/)


aux_source_directory(${SINFER_ROOT_DIR}/src/data DIR_DATA)
aux_source_directory(${SINFER_ROOT_DIR}/src/utils/ DIR_UTILS)
add_library(sinfer SHARED ${DIR_UTILS} ${DIR_DATA})

target_include_directories(sinfer PUBLIC ${SINFER_INC} ${SPDLOG_INC})


# test
add_subdirectory(${SINFER_ROOT_DIR}/3rdparty/googletest)
add_subdirectory(test)