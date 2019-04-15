cmake_minimum_required(VERSION 3.0)

project(libarchieve_example)

set(CMAKE_CXX_STANDARD 11)

find_package(LibArchive REQUIRED)

add_executable(main main.cpp)

target_link_libraries(main archive)