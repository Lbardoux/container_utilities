cmake_minimum_required(VERSION 3.0)
project(Test_container_utilities)
add_executable(Test_container_utilities
               tests.cpp
               container_utilities.hpp)

add_test(NAME unit_tests COMMAND Test_container_utilities)
include(CTest)
