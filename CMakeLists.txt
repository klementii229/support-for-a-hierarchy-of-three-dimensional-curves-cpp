cmake_minimum_required(VERSION 4.0.0)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")

project(
    Galaxy
    VERSION 0.0.1
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

find_package(OpenMP REQUIRED)
add_library(CurvesLib SHARED source/curves.cpp)
add_executable(main source/main.cpp)


target_link_libraries(main OpenMP::OpenMP_CXX)


# Связываем исполняемый файл с библиотекой
target_link_libraries(main CurvesLib)
