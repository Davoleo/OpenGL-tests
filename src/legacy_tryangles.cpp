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