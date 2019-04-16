cmake_minimum_required(VERSION 3.0)

project(boost_locale)

set(CMAKE_CXX_STANDARD 11)

find_package(ICU COMPONENTS uc i18n REQUIRED)

find_package(Boost COMPONENTS locale REQUIRED)

set (Boost_USE_STATIC_LIBS OFF) # enable dynamic linking
set (Boost_USE_MULTITHREAD ON)  # enable multithreading

add_executable(boost main.cpp)

target_link_libraries(boost Boost::locale)
