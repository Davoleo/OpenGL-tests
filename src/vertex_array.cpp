//
// Created by Davoleo on 12/08/2021.
//

#include "renderer.h"
#include "vertex_array.h"

vertex_array::vertex_array() {
    GLCall(glGenVertexArrays(1, &renderer_id));
}

vertex_array::~vertex_array() {
    GLCall(glDeleteVertexArrays(1, &renderer_id));
}

void vertex_array::bind() const {
    GLCall(glBindVertexArray(renderer_id));
}

void vertex_array::unbind() const {
    GLCall(glBindVertexArray(0));
}

void vertex_array::add_buffer(const vertex_buffer &vbo, const vertex_buffer_layout &layout) {
    this->bind();
    //Bind the buffer and setup the layout
    vbo.bind();

    const auto& elements = layout.get_elements();

    //glVertexAttribPointer works on the boundBuffer
    //Params:
    //1) The index of the attribute we want to define
    //2) The count of things inside the attribute (must be 1..4)
    //3) The type of data that we're providing
    //4) Whether OpenGL should normalize values for you (for example a color component from 0 to 255 to a float 0..1)
    //5) The total size of each vertex (sum of all the components)
    //6) The offset of each component (a pointer)
    //This is the actual line that links the VAO to the buffers because we're saying to bind the current vertex buffer
    //to the current bound VAO at offset 0

    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++) {
        const vertex_buffer_element& element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.get_stride(), (const void*) offset));
        offset += element.count * vertex_buffer_element::get_size_of_type(element.type);
    }
}
