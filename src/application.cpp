#define GLFW_DLL

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

//Static link
//#define GLEW_STATIC

/// Compiles a shader given the source code as a string and the type of shader to compile
/// \param type the type of shader to compile
/// \param source the string that contains the source code of the shader program
/// \return an UID corresponding to the compiled shader (ready to be linked)
static unsigned int compileShader(unsigned int type, const std::string& source)
{
    //Creates a shader handle and returns the id
    unsigned int id = glCreateShader(type);
    //Get a pointer to the beginning of the shader source
    const char* src = source.c_str();

    //Shader ID | Count of shaders | double pointer to the source | if the last param is null the string is espected to be null terminated
    glShaderSource(id, 1, &src, nullptr);
    //Compiles the shader and stores the result of the compilation in the parameter called GL_COMPILE_STATUS
    glCompileShader(id);

    // Retrieve the result of compiling shaders
    int result;
    //Gets a parameter of a shader object
    //GL_COMPILE_STATUS - returns GL_TRUE if the last compile operation on shader was successful, and GL_FALSE otherwise.
    //GL_INFO_LOG_LENGTH - params returns the number of characters in the information log for shader including the null termination character (i.e., the size of the character buffer required to store the information log). If shader has no information log, a value of 0 is returned.
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        //Get the length of the compile logging info and assign it to the length
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char message[length];
        //Params: The shader object id | the size of the buffer | the actual used size is returned | the char buffer for the message to be stored
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        //Frees up memory space deleting the shader linked to the
        glDeleteShader(id);
        return 0;
    }

    //Return the uid of the newly created shader
    return id;
}

/// Get the two shaders link them and a unique identifier for the shader program
/// \param vertexShader
/// \param fragmentShader
/// \return unique identifier to the linked shader program
static unsigned int linkShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
    //Creates an empty shader program object shader can be attached to
    unsigned int program = glCreateProgram();
    unsigned int vertexSh = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fragmentSh = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    //Attaching the two shaders with the empty program
    glAttachShader(program, vertexSh);
    glAttachShader(program, fragmentSh);
    //Linking the shader program TODO More docs
    glLinkProgram(program);
    //Validates the shader program: checks to see whether the executables contained in program
    //can execute given the current OpenGL state.
    //the result is stored in the param GL_VALIDATE_STATUS
    glValidateProgram(program);

    //We can delete the intermediate compiled shader objects after linking and validating the shader program
    glDeleteShader(vertexSh);
    glDeleteShader(fragmentSh);

    return program;
}

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

    //After the draw call shaders are called sequentially
    //Two kinds of shaders:
    //- Vertex Shaders (called for each vertex you're trying to render)
    //      Its primary purpose is to define where you should be seeing the vertices
    //- Fragment Shaders
    //      Also called pixel shader | is called when each pixel on the screen is rasterized
    //      Primary purpose is to determine the color each pixel should be
    //- other shaders

//    std::string vertexShader = R"GLSL(#version 330 core
//)GLSL";
//    unsigned int shader = linkShaderProgram()

    //Will reset the buffer to be bound to nothing
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

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