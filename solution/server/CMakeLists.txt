cmake_minimum_required(VERSION 3.5)

project(solution LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(server Server.cpp)
target_link_libraries(server PRIVATE core ${Boost_LIBRARY_DIRS})
target_include_directories(server PRIVATE ${CoreIncludePath} ${Boost_INCLUDE_DIRS})
