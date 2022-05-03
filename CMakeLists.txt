cmake_minimum_required(VERSION 3.16)
project(OpenGL_Tests)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/application.cpp src/legacy_tryangles.cpp src/shader_assembler.hpp src/renderer.h src/renderer.cpp src/renderer.h src/vertex_buffer.cpp src/vertex_buffer.h src/index_buffer.cpp src/index_buffer.h src/vertex_array.cpp src/vertex_array.h src/vertex_buffer_layout.hpp)

# add_library(GLFW_LIB STATIC IMPORTED)
# set_property(TARGET GLFW_LIB PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/impl/libglfw3.a)

# find_library(GLFW_LIB ${CMAKE_CURRENT_SOURCE_DIR}/lib/impl/)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/impl/)

# Link all the header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/include/)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
# link_libraries(PUBLIC ${GLFW_LIB})

#This apparently links to libraries dinamically instead of statically
# TODO find a way to make it link statically
target_link_libraries(${PROJECT_NAME} glfw3 gdi32 opengl32 glfw3dll glew32s.lib glew32.lib)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND}
        -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/lib/impl" $<TARGET_FILE_DIR:${PROJECT_NAME}>)
