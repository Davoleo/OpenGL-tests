#define GLFW_DLL

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

//Static link
//#define GLEW_STATIC

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
    float positions[6] = {
            -0.5, -0.5,
             0.0,  0.5,
             0.5, -0.5
    };

    //Will be populated with the UID of the generated object in the GPU VRAM
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    //Specifies the meaning of the buffer (in this case just a buffer of memory (array))
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //Size is in bytes | you can place NULL in place of the third parameter in case you don't want to provide initial values for the buffer
    //GL_STATIC_DRAW is the mode that this buffer will be optimized for (can be STATIC or DYNAMIC data)
    //Docs: http://docs.gl/gl4/glBufferData
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    //Params:
    //1) The index of the attribute we want to define
    //2) The count of things inside the attribute (must be 1..4)
    //3) The type of data that we're providing
    //4) Whether OpenGL should normalize values for you (for example a color component from 0 to 255 to a float 0..1)
    //5) The total size of each vertex (sum of all the components)
    //6) The offset of each component (a pointer)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);

    //Will reset the buffer to be bound to nothing
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //Legacy OpenGL Way to create a triangle
        //glBegin(GL_TRIANGLES);
        //glVertex2f(-0.5, -0.5);
        //glVertex2f(0, 0.5);
        //glVertex2f(0.5, -0.5);
        //glEnd();

        //Draw things when you don't have an index buffer
        //First parameter: the primitive you want to render
        //Second Parameter: the offset from the first item of the data buffer
        //Third Parameter: the number of indices (vertices) you want to render
        //It will draw depending ON THE BOUND buffer (you don't need to pass the buffer since openGL works as a state machine)
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}