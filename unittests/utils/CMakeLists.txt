add_executable(
  utils_test
  utest_log.cpp
  utest_observable.cpp
  utest_queue.cpp
)

target_link_libraries(
  utils_test
  GTest::gtest_main
  GTest::gmock_main
  utils
)

include(GoogleTest)
gtest_discover_tests(utils_test)

