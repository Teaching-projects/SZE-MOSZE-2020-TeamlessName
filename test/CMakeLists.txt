cmake_minimum_required(VERSION 2.6)
 
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

project("Unittest")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 

# and the GTest and pthread library
add_executable(runTests parser_test.cpp ../JSON.cpp ../Monster.cpp ../Hero.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
