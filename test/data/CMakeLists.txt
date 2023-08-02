enable_testing()

add_executable(test_tensor test_tensor.cc)
target_link_libraries(test_tensor GTest::gtest_main)
target_include_directories(test_tensor PUBLIC ${SINFER_INC} ${SPDLOG_INC})