cmake_minimum_required(VERSION 3.25)
project(reflection_demo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(/opt/hobby-refroot/boost_1_89_0)

add_executable(reflection_demo reflection_boost_pfr.cpp)