cmake_minimum_required(VERSION 3.16)

# Название проекта
project(racess)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Устанавливаем пути для вывода исполняемых файлов и библиотек
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Добавляем подпроекты
add_subdirectory(libTransport)
add_subdirectory(libMassive)
add_subdirectory(app)
