cmake_minimum_required(VERSION 3.10)
project(Asynchrone)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем поддержку потоков
find_package(Threads REQUIRED)

add_executable(Asynchrone main.cpp)

# Линкуем pthread (если требуется)
target_link_libraries(Asynchrone PRIVATE Threads::Threads)