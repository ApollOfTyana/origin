cmake_minimum_required(VERSION 3.10)
project(Concurent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем поддержку потоков
find_package(Threads REQUIRED)

add_executable(Concurent main.cpp data.cpp data.h)

# Линкуем pthread (если требуется)
target_link_libraries(Concurent PRIVATE Threads::Threads)