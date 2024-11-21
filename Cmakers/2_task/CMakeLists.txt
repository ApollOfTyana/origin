cmake_minimum_required(VERSION 3.10)
project(cmake_Figure VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(cmake_figures src/main.cpp src/figure_base.cpp src/quadrangle.cpp src/triangle.cpp)

install(TARGETS cmake_figures RUNTIME DESTINATION bin)