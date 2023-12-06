cmake_minimum_required(VERSION 3.20)

project(UniversalConverter VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(UniversalConverter
    src/main.cpp
    src/BigInt.cpp
    inc/Interface.hpp
    inc/BigInt.hpp
    src/Interface.cpp
)

target_link_libraries(UniversalConverter PRIVATE Qt6::Widgets)