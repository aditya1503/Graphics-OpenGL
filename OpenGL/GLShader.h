#ifndef GLSHADER_H
#define GLSHADER_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "GLIncludes.h"

class GLShader
{
protected:
	GLuint shader_handle;
	std::string shader_file;

	GLuint LoadShader(const std::string fname, int type);
public:
	GLShader(const std::string &fname, int type);
	GLuint GetHandle() const;
};

class GLProgram
{
protected:
	GLuint program_handle;
	std::vector<GLShader> shader_list;

	GLuint Compile(const std::vector<GLShader> &shaders);	
public:

	GLProgram(std::vector<GLShader> &shaders);
	GLuint GetHandle() const;
	
	void SetUniform(const std::string &name, float value) const;
	void SetUniform(const std::string &name, int value) const;
	void SetUniform(const std::string &name, glm::mat4 &value) const;
	void SetUniform(const std::string &name, glm::vec4 &value) const;
	void SetUniform(const std::string &name, glm::vec3 &value) const;
	void SetUniform(const std::string &name, glm::vec2 &value) const;
	GLint GetUniformLocation(const std::string &name) const;
};

#endif