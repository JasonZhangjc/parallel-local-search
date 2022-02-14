cmake_minimum_required(VERSION 2.8.9)
project(PLS_QUBO)

add_compile_options(-std=c++11)
add_compile_options(-std=c++14)
add_compile_options(-std=c++17)

file(GLOB SOURCES "src/*.cpp")

add_executable(PLS_QUBO ${SOURCES})