//
// Created by Davoleo on 12/08/2021.
//

#ifndef OPENGL_TESTS_VERTEX_BUFFER_H
#define OPENGL_TESTS_VERTEX_BUFFER_H


class vertex_buffer {
private:
    unsigned int renderer_id;
public:
    vertex_buffer(const void* data, unsigned int size);
    ~vertex_buffer();

    void bind() const;
    void unbind() const;
};


#endif //OPENGL_TESTS_VERTEX_BUFFER_H
