cmake_minimum_required(VERSION 3.2)
project(DataStreamingCPP_tst)


add_executable(AlgorithmTest algorithm_test.cpp)
target_link_libraries(
    AlgorithmTest
  GTest::gtest_main
)

add_executable(GraphTest graph_test.cpp)
target_link_libraries(
    GraphTest
  GTest::gtest_main
)

add_executable(ListTest list_test.cpp)
target_link_libraries(
    ListTest
  GTest::gtest_main
)

add_executable(PathTest path_test.cpp)
target_link_libraries(
    PathTest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(AlgorithmTest GraphTest ListTest PathTest)

#target_compile_options(AlgorithmTest PRIVATE -Werror -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wnull-dereference -Wdouble-promotion -Wformat=2)
