find_package(ICU COMPONENTS uc i18n REQUIRED)

find_package(Boost COMPONENTS locale REQUIRED)

add_executable(boost main.cpp)

target_link_libraries(boost Boost::locale)
