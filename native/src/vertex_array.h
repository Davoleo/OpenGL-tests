//
// Created by Davoleo on 12/08/2021.
//

#ifndef OPENGL_TESTS_VERTEX_ARRAY_H
#define OPENGL_TESTS_VERTEX_ARRAY_H

#include "vertex_buffer.h"

class vertex_buffer_layout;

class vertex_array {
private:
    //The numeric id that identifies the current object and context
    unsigned int renderer_id;

public:
    vertex_array();
    ~vertex_array();

    void add_buffer(const vertex_buffer& vbo, const vertex_buffer_layout& layout);

    void bind() const;
    void unbind() const;
};


#endif //OPENGL_TESTS_VERTEX_ARRAY_H
