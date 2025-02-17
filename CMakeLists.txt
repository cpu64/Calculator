cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/6910c9d9165801d8827d628cb72eb7ea9dd538c5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  Calculator
  main.cpp calculator.cpp token.cpp
)

add_executable(
  Calculator_test
  test/test_calculations.cpp calculator.cpp token.cpp
)

add_executable(
  Preprocessor_test
  test/test_preprocessor.cpp calculator.cpp token.cpp
)

target_link_libraries(
  Calculator_test
  GTest::gtest_main
)

target_link_libraries(
  Preprocessor_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Calculator_test)
gtest_discover_tests(Preprocessor_test)
