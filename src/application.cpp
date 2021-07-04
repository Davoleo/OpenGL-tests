#define GLFW_DLL

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>

//Static link
//#define GLEW_STATIC

#include "shader_assembler.hpp"

#pragma region ERROR HANDLING

#define ASSERT(x) if (!(x)) __builtin_trap()

#define GLCall(x) GLClearError(); \
x;                                \
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

static void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << ") : " << function
        << " " << file << ":" << line << std::endl;
        return false;
    }

    return true;
}

#pragma endregion

#define DAV_TESTS_SHAPE 1

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current (creates the rendering context) */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    //Print the supported OpenGL version
    std::cout << glGetString(GL_VERSION) << std::endl;

    //Concepts
    //To draw a triangle in modern OpenGL we'll need 2 things
    //1) a Vertex Buffer (a buffer used to store bytes in memory (although in the VRAM))
    //2) a Shader is a program that runs on the GPU

    //You select a buffer and a shader which are based on the status of the GPU and then the GPU draws the triangle depending on those two things
    // **State Machine**

    //Defining the buffer outside the frame loop
    float basicTriangle[6] = {
            -0.5f, -0.5f,
             0.0,  0.5f,
             0.5f, -0.5f
    };

    //Made up of 2 triangles but identical vertices are deduplicated
    float square[] = {
            -0.5f, -0.5f,   //0
            0.5f, -0.5f,    //1
            0.5f, 0.5f,     //2
            -0.5f, 0.5f     //3
    };

    //Called index buffer
    unsigned int squareIndices[] = {
            0, 1, 2,
            2, 3, 0
    };

#if DAV_TESTS_SHAPE == 0
    //Will be populated with the UID of the generated object in the GPU VRAM
    unsigned int buffer;
    GLCall(glGenBuffers(1, &buffer));
    //Specifies the meaning of the buffer (in this case just a buffer of memory (array))
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    //Size is in bytes | you can place NULL in place of the third parameter in case you don't want to provide initial values for the buffer
    //GL_STATIC_DRAW is the mode that this buffer will be optimized for (can be STATIC or DYNAMIC data)
    //Docs: http://docs.gl/gl4/glBufferData
    GLCall(glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), basicTriangle, GL_STATIC_DRAW));

#elif DAV_TESTS_SHAPE == 1

    //GPUs have triangles as their basic primitive shape
    //since they have the lowest number of vertices to create a flat shape with a normal that points in a single direction
    //all the other shapes are derivatives (like a square it's just 2 triangles)
    //They allow us to reuse vertices instead of having to repeat coincident vertices like when we're drawing a square or whenever there are adjacent triangles

    //ibo stands for Index Buffer Object | object id that represents the index buffer
    unsigned int ibo;
    GLCall(glGenBuffers(1, &ibo));
    //Specifies the meaning of the buffer
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof (unsigned int), squareIndices, GL_STATIC_DRAW));
#endif

    //glVertexAttribPointer works on the boundBuffer
    //Params:
    //1) The index of the attribute we want to define
    //2) The count of things inside the attribute (must be 1..4)
    //3) The type of data that we're providing
    //4) Whether OpenGL should normalize values for you (for example a color component from 0 to 255 to a float 0..1)
    //5) The total size of each vertex (sum of all the components)
    //6) The offset of each component (a pointer)
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
    GLCall(glEnableVertexAttribArray(0));

    ShaderProgramSource src = parseShader("res/shaders/basic.shader");
//    std::cout << "VERTEX SHADER" << std::endl;
//    std::cout << src.vertex << std::endl;
//    std::cout << "FRAGMENT SHADER" << std::endl;
//    std::cout << src.fragment << std::endl;

    unsigned int shader = linkShaderProgram(src.vertex, src.fragment);
    //Bind the shader to use when drawing
    GLCall(glUseProgram(shader));

    ///--- Uniform here ---///
    //After the shader is bound 4f because we're passing 4 floats
    //Retrieve the location of the variable
    GLCall(int colorLocation = glGetUniformLocation(shader, "u_Color"));
    //Might also return -1 if the uniform in the shader is unused
    ASSERT(colorLocation != -1);
    GLCall(glUniform4f(colorLocation, 0.2F, 0.3F, 0.8F, 1.0F));
    ///--- Uniform here ---///

    //Will reset the buffer to be bound to nothing
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

#if DAV_TESTS_SHAPE == 0
        //Draw things when you don't have an index buffer
        //First parameter: the primitive you want to render
        //Second Parameter: the offset from the first item of the data buffer
        //Third Parameter: the number of indices (vertices) you want to render
        //It will draw depending ON THE BOUND buffer (you don't need to pass the buffer since openGL works as a state machine)
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
#elif DAV_TESTS_SHAPE == 1

        //Uniforms are a way to pass data to the GPU every draw call
        //Drawing 2 triangles | 6 INDICES | The type (HAS TO BE GL_UNSIGNED_INT in this case) | Since we've assigned the indices earlier
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
#endif

        /* Swap front and back buffers */
        GLCall(glfwSwapBuffers(window));

        /* Poll for and process events */
        GLCall(glfwPollEvents());
    }

    //Delete the shader program to clean up resources
    GLCall(glDeleteProgram(shader));

    glfwTerminate();
    return 0;
}