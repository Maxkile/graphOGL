cmake_minimum_required(VERSION 3.13)
project(scene)

set(CMAKE_CXX_STANDARD 11)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS ${GCC_COVERAGE_COMPILE_FLAGS})
set(OGflags -lGLEW -lglfw -lGL -lX11 -lpthread -lXrandr )
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

add_executable(scene scene.cpp src/Callbacks.cpp src/ShaderProgram.cpp src/Shader.cpp)
target_link_libraries(scene ${OGflags} ${GLFW3_LIBRANIES} ${GLEW_LIBRANIES} ${CMAKE_CURRENT_SOURCE_DIR}/lib/SOIL/libSOIL.so
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/SOIL/libSOIL.so.1 ${CMAKE_CURRENT_SOURCE_DIR}/lib/SOIL/libSOIL.so.1.07-20071110)#todo:change linking type for SOIL
