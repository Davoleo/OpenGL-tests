cmake_minimum_required(VERSION 3.16)
project(OpenGL_Tests)

set(CMAKE_CXX_STANDARD 14)

# Link all the header files
include_directories(D:/Everything/Coding/libs/C/include)

set(OGL_LIBS "${CMAKE_SOURCE_DIR}/lib")
add_library(GLAD "D:/Everything/Coding/libs/C/include/glad/glad.h" "${OGL_LIBS}/glad.c")

# Link to the compiled GLFW library
link_libraries(D:/Everything/Coding/libs/C/lib/glfw3.dll)

add_executable(OpenGL_Tests main.cpp)