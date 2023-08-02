enable_testing()

#spdlog
#set(SPDLOG_INC ${SINFER_ROOT_DIR}/3rdparty/spdlog/include/)


add_executable(test_gtest test_gtest.cc)
target_link_libraries(test_gtest GTest::gtest_main)

add_executable(test_spdlog test_spdlog.cc)
target_link_libraries(test_spdlog GTest::gtest_main)
target_include_directories(test_spdlog PUBLIC ${SPDLOG_INC})

add_executable(test_logger test_logger.cc)
target_link_libraries(test_logger GTest::gtest_main sinfer)

include(GoogleTest)
gtest_discover_tests(test_gtest)
gtest_discover_tests(test_spdlog)