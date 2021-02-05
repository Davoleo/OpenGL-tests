cmake_minimum_required(VERSION 3.16)
project(OpenGL_Tests)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} src/application.cpp)

find_path(INCLUDES glfw.h D:/Everything/Coding/libs/C/include/GLFW)

# Link all the header files
include_directories(D:/Everything/Coding/libs/C/include)

# Link to the compiled lib_src library
find_library(OPENGL_LIBS glfw3 D:/Everything/Coding/libs/C/lib)

target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_LIBS})
