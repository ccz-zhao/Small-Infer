enable_testing()

add_executable(test_tensor test_tensor.cc)
target_link_libraries(test_tensor GTest::gtest_main)
target_link_libraries(test_tensor sinfer)

include(GoogleTest)
gtest_discover_tests(test_tensor)