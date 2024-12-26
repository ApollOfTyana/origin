# Создаем вторую динамическую библиотеку
add_library(MassiveLib SHARED
    massive.cpp)

# Устанавливаем флаги для правильной экспорта символов (для Windows)
set_target_properties(MassiveLib PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON CXX_STANDARD 11
CXX_STANDARD_REQUIRED ON)

# Указываем пути для инклуда, если нужно
target_include_directories(MassiveLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})