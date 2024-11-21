cmake_minimum_required(VERSION 3.10)
project(cmake_project VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(cmake_program src/main.cpp)

install(TARGETS cmake_program RUNTIME DESTINATION bin)