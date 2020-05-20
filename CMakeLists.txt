cmake_minimum_required(VERSION 3.16)
project(OpenGL_Tests)

set(CMAKE_CXX_STANDARD 14)

include_directories(D:/Everything/Coding/libs/C/include)
link_libraries(D:/Everything/Coding/libs/C/lib/glfw3.dll)

add_executable(OpenGL_Tests main.cpp)