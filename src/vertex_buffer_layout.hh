//
// Created by Davoleo on 12/08/2021.
//

#ifndef OPENGL_TESTS_VERTEX_BUFFER_LAYOUT_HPP
#define OPENGL_TESTS_VERTEX_BUFFER_LAYOUT_HPP

#include <vector>
#include <GL/glew.h>

#include "renderer.h"

struct vertex_buffer_element {
    unsigned int type;
    unsigned int count;
    //GLbool
    unsigned char normalized;

    static unsigned int get_size_of_type(unsigned int type) {
        switch (type) {
            case GL_FLOAT:
                return sizeof(float);
            case GL_UNSIGNED_INT:
                return sizeof(unsigned int);
            case GL_UNSIGNED_BYTE:
                return sizeof(unsigned char);
            default:
                return 0;
        }
    }
};

class vertex_buffer_layout {
private:
    std::vector<vertex_buffer_element> elements;
    unsigned int stride;
public:
    vertex_buffer_layout() : stride(0) {

    }

    template<unsigned int T>
    void push(unsigned int count) {
        unsigned int type_size = vertex_buffer_element::get_size_of_type(T);
        ASSERT(type_size > 0);

        elements.push_back({T, count, GL_FALSE});
        stride += count * type_size;
    }

    inline unsigned int get_stride() const {
        return stride;
    }

    inline const std::vector<vertex_buffer_element>& get_elements() const {
        return elements;
    }
};

//Template Specializations
//template<>
//void vertex_buffer_layout::push<float>(unsigned int count) {
//    elements.push_back({GL_FLOAT, count, GL_FALSE});
//    stride += vertex_buffer_element::get_size_of_type(GL_FLOAT);
//}
//
//template<>
//void vertex_buffer_layout::push<unsigned int>(unsigned int count) {
//    elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
//    stride += vertex_buffer_element::get_size_of_type(GL_UNSIGNED_INT);
//}
//template<>
//void vertex_buffer_layout::push<unsigned char>(unsigned int count) {
//    elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
//    stride += vertex_buffer_element::get_size_of_type(GL_UNSIGNED_BYTE);
//}

#endif //OPENGL_TESTS_VERTEX_BUFFER_LAYOUT_HPP
