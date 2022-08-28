//
// Created by Davoleo on 12/08/2021.
//

#include "renderer.h"
#include "index_buffer.h"

index_buffer::index_buffer(const unsigned int* data, unsigned int count) : count(count) {
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &renderer_id));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

index_buffer::~index_buffer() {
    GLCall(glDeleteBuffers(1, &renderer_id));
}

void index_buffer::bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id));
}
void index_buffer::unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
