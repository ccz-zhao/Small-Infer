enable_testing()

add_executable(
  test_gtest
  test_gtest.cc
)
target_link_libraries(
  test_gtest
  GTest::gtest_main
)

add_executable(
  test_spdlog
  test_spdlog.cc
)
target_link_libraries(
  test_spdlog
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_gtest)
gtest_discover_tests(test_spdlog)