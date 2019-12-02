cmake_minimum_required(VERSION 3.0)

project(mgraph)

add_executable(mgraph main.cpp)

install(TARGETS mgraph RUNTIME DESTINATION bin)
