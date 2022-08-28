//
// Created by Davoleo on 12/08/2021.
//

#ifndef OPENGL_TESTS_RENDERER_H
#define OPENGL_TESTS_RENDERER_H

#include <GLEW/glew.h>

#pragma region ERROR HANDLING

#define ASSERT(x) if (!(x)) __debugbreak()
#define GLCall(x) GLClearError(); \
x;                                \
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#pragma endregion

#endif //OPENGL_TESTS_RENDERER_H
