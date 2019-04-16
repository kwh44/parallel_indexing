find_package(LibArchive REQUIRED)

add_executable(arch main.cpp)

target_link_libraries(arch archive)