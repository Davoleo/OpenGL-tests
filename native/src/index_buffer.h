//
// Created by Davoleo on 12/08/2021.
//

#ifndef OPENGL_TESTS_INDEX_BUFFER_H
#define OPENGL_TESTS_INDEX_BUFFER_H

//GPUs have triangles as their basic primitive shape
//since they have the lowest number of vertices to create a flat shape with a normal that points in a single direction
//all the other shapes are derivatives (like a square it's just 2 triangles)
//They allow us to reuse vertices instead of having to repeat coincident vertices like when we're drawing a square or whenever there are adjacent triangles
//ibo stands for Index Buffer Object | object id that represents the index buffer
class index_buffer {
private:
    unsigned int renderer_id;
    unsigned int count;
public:
    index_buffer(const unsigned int* data, unsigned int size);
    ~index_buffer();

    void bind() const;
    void unbind() const;

    inline unsigned int get_count() const {
        return count;
    }
};


#endif //OPENGL_TESTS_INDEX_BUFFER_H
