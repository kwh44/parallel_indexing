cmake_minimum_required(VERSION 3.0)

project(parallel_indexing)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost COMPONENTS locale REQUIRED)

find_package(Threads REQUIRED)

find_package(LibArchive REQUIRED)

find_package(ICU COMPONENTS uc i18n REQUIRED)

# add_compile_options("-DDEBUG")

set(Boost_USE_STATIC_LIBS OFF)

set(Boost_USE_MULTITHREAD ON)

include_directories(include)

add_executable(parallel_indexing main.cpp include/read_config.hpp src/read_config.cpp
        include/measure_time.hpp src/read_from_file.cpp include/read_from_file.hpp)

target_link_libraries(parallel_indexing Boost::locale archive)
