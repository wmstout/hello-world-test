cmake_minimum_required(VERSION 3.15)
project(hello_world VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hello_world
    src/main.cpp
    src/greeter.cpp
    src/utils.cpp
)

target_include_directories(hello_world PRIVATE src)
