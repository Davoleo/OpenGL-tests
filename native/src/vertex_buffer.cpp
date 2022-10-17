//
// Created by Davoleo on 12/08/2021.
//

#include "renderer.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.hpp"

vertex_buffer::vertex_buffer(const void *data, unsigned int size) {
    GLCall(glGenBuffers(1, &renderer_id));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, renderer_id));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

vertex_buffer::~vertex_buffer() {
    GLCall(glDeleteBuffers(1, &renderer_id));
}

void vertex_buffer::bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, renderer_id));
}
void vertex_buffer::unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
