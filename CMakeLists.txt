cmake_minimum_required(VERSION 3.18)

project(libsxc VERSION 0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED YES)

add_compile_options(-Wall -Wextra)

set(LIB_NAME "sxc")

add_subdirectory(src)

enable_testing()
add_subdirectory(test)

