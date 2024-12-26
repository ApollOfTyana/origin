# Указываем, что создаем динамическую библиотеку
add_library(TransportLib SHARED
    race.cpp
    transport.cpp
    ${CMAKE_SOURCE_DIR}/libMassive/massive.cpp)

# Устанавливаем флаги для правильной экспорта символов (для Windows)
set_target_properties(TransportLib PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON CXX_STANDARD 11
CXX_STANDARD_REQUIRED ON)

# Указываем, какие заголовочные файлы необходимы для этой библиотеки
target_include_directories(TransportLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/libMassive)

