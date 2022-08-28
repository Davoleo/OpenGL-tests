//
// Created by Davoleo on 18/05/2021.
//

#ifndef OPENGL_TESTS_SHADER_ASSEMBLER_HPP
#define OPENGL_TESTS_SHADER_ASSEMBLER_HPP

#include <fstream>

struct ShaderProgramSource
{
    std::string vertex;
    std::string fragment;
};

static ShaderProgramSource parseShader(const std::string& filepath) {
    std::ifstream inputStream(filepath);

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream shaders[2];
    ShaderType type = ShaderType::NONE;
    while (getline(inputStream, line)) {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else {
            if (line.substr(0, 2) != "//")
                shaders[(int)type] << line << '\n';
        }
    }

    return { shaders[0].str(), shaders[1].str() };
}

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

    //Shader ID | Count of shaders | double pointer to the source | if the last param is null the string is expected to be null terminated
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
        char* message = (char*) alloca(length * sizeof(char)); //MSVC
        //char message[length]; // only works on gcc apparently
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

#endif //OPENGL_TESTS_SHADER_ASSEMBLER_HPP
