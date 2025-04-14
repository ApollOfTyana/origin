cmake_minimum_required(VERSION 3.14)
project(PostgreSQLExample CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Unicode
if(WIN32)
    add_compile_options(/utf-8)
else()
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

# macOS -- Homebrew
if(APPLE)
    include_directories(/opt/homebrew/include /usr/local/include)
    link_directories(/opt/homebrew/lib /usr/local/lib)
    set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
endif()

find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(LIBPQXX QUIET libpqxx)
endif()

if(NOT LIBPQXX_FOUND)
    message(STATUS "libpqxx not found via pkg-config. Trying local directory...")
    
    # Windows -- vcpkg
    if(WIN32)
        set(VCPKG_PATH "C:/vcpkg/installed/x64-windows" CACHE PATH "vcpkg installation path")
        include_directories(${VCPKG_PATH}/include)
        link_directories(${VCPKG_PATH}/lib)
    endif()

    # loc head libpqxx
    include_directories(${PROJECT_SOURCE_DIR}/libpqxx/include)
    
    # static
    if(EXISTS "${PROJECT_SOURCE_DIR}/libpqxx/CMakeLists.txt")
        add_subdirectory(${PROJECT_SOURCE_DIR}/libpqxx)
        set(LIBPQXX_LIBRARIES pqxx)
        message(STATUS "Using local libpqxx sources")
    else()
        message(FATAL_ERROR "libpqxx not found. Install via package manager or place sources in libpqxx directory.")
    endif()
endif()

find_package(PostgreSQL REQUIRED)

add_executable(my_program main.cpp)

target_link_libraries(my_program PRIVATE
    ${LIBPQXX_LIBRARIES}
    PostgreSQL::PostgreSQL
)

# frameworks Windows
if(WIN32)
    target_link_libraries(my_program PRIVATE
        ws2_32  # Winsock
        bcrypt  # Криптография
        crypt32 # Безопасность
        advapi32 # Службы Windows
    )
endif()

# frameworks macOS
if(APPLE)
    target_link_libraries(my_program PRIVATE
        "-framework CoreFoundation"
        "-framework Security"
    )
endif()

# PostgreSQL == UTF8
if(POSTGRESQL_FOUND)
    target_compile_definitions(my_program PRIVATE
        PQXX_HAVE_CXX_UTF8=1
    )
endif()