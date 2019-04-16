cmake_minimum_required(VERSION 3.0)

project(parallel_indexing)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost COMPONENTS system REQUIRED)

find_package(Threads REQUIRED)

# add_compile_options("-DDEBUG")

add_subdirectory(libarchive_read_compressed_files_content)
add_subdirectory(boost_locale)
add_executable(parallel_indexing main.cpp read_config.hpp read_config.cpp measure_time.hpp)

target_link_libraries(parallel_indexing Boost::system Threads::Threads)
