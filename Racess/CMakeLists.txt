cmake_minimum_required(VERSION 3.16)

# Название проекта
project(racess)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Для студии ставим флаг, что кодировка исходников UTF-8
if(MSVC)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

# Устанавливаем пути для вывода исполняемых файлов и библиотек
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Добавляем подпроекты
add_subdirectory(libTransport)
add_subdirectory(libMassive)
add_subdirectory(app)
