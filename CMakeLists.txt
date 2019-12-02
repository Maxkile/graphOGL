cmake_minimum_required(VERSION 3.13)
project(test)

set(CMAKE_CXX_STANDARD 11)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS ${GCC_COVERAGE_COMPILE_FLAGS})
set(OGflags -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr )
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
include_directories(${GLFW3_LIBRANIES},${GLEW_LIBRANIES})
add_executable(test main.cpp functions.cpp functions.hpp)
target_link_libraries(test ${OGflags} ${GLFW3_LIBRANIES} ${GLEW_LIBRANIES})
