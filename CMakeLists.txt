cmake_minimum_required(VERSION 3.24)
project(Ini_OpenGL)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(dependencies/glfw)

include_directories(dependencies/glad/include)
add_library(glad dependencies/glad/src/glad.c)

target_link_libraries(${PROJECT_NAME} glfw opengl32 glad)
