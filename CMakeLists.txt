cmake_minimum_required(VERSION 3.0)

project(parallel_indexing)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost COMPONENTS system REQUIRED)

find_package(Threads REQUIRED)

add_executable(main main.cpp)

target_link_libraries(main Boost::system Threads::threads)
