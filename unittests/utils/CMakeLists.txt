add_executable(
  utils_test
  test.cpp
)

target_link_libraries(
  utils_test
  GTest::gtest_main
  utils
)

include(GoogleTest)
gtest_discover_tests(utils_test)

