add_executable(client main.cpp)

# Линкуем с обеими библиотеками
target_link_libraries(client PRIVATE TransportLib MassiveLib)

# Указываем пути к заголовочным файлам библиотек
target_include_directories(client PRIVATE
    ${CMAKE_SOURCE_DIR}/libTransport
    ${CMAKE_SOURCE_DIR}/libMassive)