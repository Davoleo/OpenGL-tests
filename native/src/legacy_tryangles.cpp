//
// Created by Davoleo on 04/03/2021.
//

#include <GLEW/glew.h>

void beginGLTryangles() {
    //Legacy OpenGL Way to create a triangle
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();
}

#if false

//Legacy Draw Array thing, first triangles in modern openGL

        //Draw things when you don't have an index buffer
        //First parameter: the primitive you want to render
        //Second Parameter: the offset from the first item of the data buffer
        //Third Parameter: the number of indices (vertices) you want to render
        //It will draw depending ON THE BOUND buffer (you don't need to pass the buffer since openGL works as a state machine)
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));


    //Defining the buffer outside the frame loop
    float basicTriangle[6] = {
            -0.5f, -0.5f,
            0.0,  0.5f,
            0.5f, -0.5f
    };

    //Will be populated with the UID of the generated object in the GPU VRAM
    unsigned int buffer;
    unsigned int vao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glGenBuffers(1, &buffer));

    GLCall(glBindVertexArray(vao));

    //Specifies the meaning of the buffer (in this case just a buffer of memory (array))
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    //Size is in bytes | you can place NULL in place of the third parameter in case you don't want to provide initial values for the buffer
    //GL_STATIC_DRAW is the mode that this buffer will be optimized for (can be STATIC or DYNAMIC data)
    //Docs: http://docs.gl/gl4/glBufferData
    GLCall(glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), basicTriangle, GL_STATIC_DRAW));

#endif
