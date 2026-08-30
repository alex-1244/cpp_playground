cmake_minimum_required(VERSION 4.2)
project(cppone)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra)

add_executable(cppone main.cpp)
add_executable(sensor_stats 01_sensor_stats.cpp)
add_executable(predictions predictions.cpp)
