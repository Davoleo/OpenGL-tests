#pragma once
#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
	std::string vertex;
	std::string fragment;
};


class shader
{
private:
	//Stored for debugging purposes only [Otherwise just used in the constructor of the shader]
	std::string filepath;

	//The Shader id
	unsigned int rendererId;

	std::unordered_map<std::string, int> uniformLocationCache;

public:
	shader(const std::string& filepath);
	~shader();

	void bind() const;
	void unbind() const;

	void set_uniform1f(const std::string& name, float value);
	void set_uniform4f(const std::string& name, float v0, float v1, float f2, float f3);

private:
	ShaderProgramSource parse_shader(const std::string& filepath);
	unsigned int compile_shader(unsigned int type, const std::string& source);
	unsigned int create_shader(const std::string& vertexShader, const std::string& fragmentShader);
	int get_uniform_location(const std::string& name);
};

