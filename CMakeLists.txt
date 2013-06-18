cmake_minimum_required(VERSION 2.6)
project(CPP_UNITS)

set(cmake_cxx_compiler g++)
set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

add_executable(units_test Units_test.cpp)


