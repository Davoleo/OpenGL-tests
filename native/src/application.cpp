#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>

#include "renderer.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "shader.h"
#include "vertex_array.h"
#include "vertex_buffer_layout.hpp"

void handleInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

#define DAV_TESTS_SHAPE 1

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    //Should synchronize framerate with the monitor VSync or the refresh-rate
    glfwSwapInterval(1);

    //Print the supported OpenGL version
    std::cout << glGetString(GL_VERSION) << std::endl;

    //Concepts
    //To draw a triangle in modern OpenGL we'll need 2 things
    //1) a Vertex Buffer (a buffer used to store bytes in memory (although in the VRAM))
    //2) a Shader is a program that runs on the GPU

    //You select a buffer and a shader which are based on the status of the GPU and then the GPU draws the triangle depending on those two things
    // **State Machine**

    shader shader("res/shaders/basic.shader");
    //Bind the shader to use when drawing
    shader.bind();

    //Made up of 2 triangles but identical vertices are deduplicated
    float square[] = {
            -0.5f, -0.5f, //0
            0.5f, -0.5f,  //1
            0.5f, 0.5f,   //2
            -0.5f, 0.5f,  //3
    };

    //Called index buffer
    unsigned int squareIndices[] = {
            0, 1, 2,
            2, 3, 0
    };

    auto* squareVBO = new vertex_buffer(square, sizeof(square));
    auto* squareIBO = new index_buffer(squareIndices, 6);

    //The VAO Stores the configuration (layout) that is bind via glVertexAttribPointer AND the Vertex Buffer (?)
    vertex_array vao;
    vertex_buffer_layout layout;
    layout.push<GL_FLOAT>(2);
    vao.add_buffer(*squareVBO, layout);

    ///--- Uniform here ---///
    shader.bind();
    shader.set_uniform4f("u_Color", 0.2F, 0.3F, 0.8F, 1.0F);

    float red = 0.0F;
    float increment = 0.05F;
    ///--- Uniform here ---///

    //will draw poligons in wireframe mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Unbind VBO and VAO once everything is setup
    vao.unbind();
    squareVBO->unbind();
    squareIBO->unbind();

    renderer renderer;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Rendering here! */
        renderer.clear();

        //Handle any input that is sent
        handleInput(window);


        if (red > 1.0F)
            increment = -0.05F;
        else if (red < 0)
            increment = 0.05F;

        red += increment;

        shader.bind();
        //Uniforms are a way to pass data to the GPU every draw call
        shader.set_uniform4f("u_Color", red, 0.3F, 0.8F, 1.0F);
        //Drawing 2 triangles [Primitive hint] | 6 INDICES | The type (HAS TO BE GL_UNSIGNED_INT in this case) | Since we've assigned the indices earlier
        renderer.draw(vao, *squareIBO, shader);

        //These handle the render loop
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

#if DAV_TESTS_SHAPE == 1
    delete squareVBO;
    delete squareIBO;
#endif

    glfwTerminate();
    return 0;
}