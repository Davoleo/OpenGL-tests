//
// Created by Davoleo on 12/08/2021.
//

#include "renderer.h"

#include <iostream>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << ") : " << function
        << " " << file << ":" << line << std::endl;
        return false;
    }

    return true;
}

void renderer::clear() const
{
	//Changes the clear color (default is black)
    //GLCall(glClearColor(0.2F, 0.3F, 0.3F, 1.0F));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void renderer::draw(const vertex_array& vao, const index_buffer& ibo, const shader& shader) const
{
    shader.bind();
	vao.bind();
	ibo.bind();
	GLCall(glDrawElements(GL_TRIANGLES, ibo.get_count(), GL_UNSIGNED_INT, nullptr));
}

//Legacy application.cpp code
/*
  Draw things when you don't have an index buffer
  First parameter: the primitive you want to render
  Second Parameter: the offset from the first item of the data buffer
  Third Parameter: the number of indices (vertices) you want to render
  It will draw depending ON THE BOUND buffer (you don't need to pass the buffer since openGL works as a state machine)
  GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
 */
