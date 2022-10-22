#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>

#include "renderer.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "shader.h"
#include "texture.h"
#include "vertex_array.h"
#include "vertex_buffer_layout.hpp"

void handleInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

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
    //  The 2 floats at the right in each row represent texture coordinates
    float square[] = {
            -0.5f, -0.5f, 0.0f, 0.0f, //0
            0.5f, -0.5f, 1.0f, 0.0f,  //1
            0.5f, 0.5f, 1.0f, 1.0f,  //2
            -0.5f, 0.5f, 0.0f, 1.0f //3
    };

    //Called index buffer
    unsigned int square_indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    //Blending:
    //How do we render something that is partially/fully transparent
    //Blending determines how to combine the output color with what is already on the buffer of the GPU
    //Output: The color output from the fragment shader [source]
    //Target buffer: buffer the fragment shader is drawing to [destination]
    //
    //3 Ways to control blending:
    //- glEnabled(GL_BLEND) - glDisable(GL_BLEND) | disabled by default
    //- glBlendFunc(src, dest) | controls how to blend the two RGBA colors -- by default src is kept as is [multiplied by 1] & old dest is destroyed [multiplied by 0]
    //  - src by default is GL_ONE
	//  - dest by default is GL_ZERO
    //- glBlendEquation(mode)
    //  - mode specifies how to combine src and dest | by default mode is GL_FUNC_ADD
    //Enable Basic Blending
    GLCall(glEnable(GL_BLEND));
    //Blending function:
    //source alpha value  = 1 - source alpha values
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	//The VAO Stores the configuration (layout) that is bind via glVertexAttribPointer AND the Vertex Buffer (?)
    vertex_array vao;

	vertex_buffer vbo(square, 4 * 4 * sizeof(float)); //4 Floats per vertex

    vertex_buffer_layout layout;
    layout.push<GL_FLOAT>(2);
    layout.push<GL_FLOAT>(2);

    vao.add_buffer(vbo, layout);
    index_buffer ibo(square_indices, 6);

    ///--- Uniform here ---///
    shader.bind();
    shader.set_uniform4f("u_Color", 0.2F, 0.3F, 0.8F, 1.0F);

    float red = 0.0F;
    float increment = 0.05F;
    ///--- Uniform here ---///

    //will draw poligons in wireframe mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    texture texture("res/textures/rouxls_kaard.png");
    //Bound to slot 0 so uniform value should be 0
    texture.bind(); 
    shader.set_uniform1i("u_Texture", 0);

	//Unbind VBO and VAO once everything is setup
    vao.unbind();
    vbo.unbind();

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
        renderer.draw(vao, ibo, shader);

        //These handle the render loop
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}