#include <iostream>
#include <string>
#include <vector>

#include "GLShader.h"
#include "GLUtils.h"

GLuint GLShader::LoadShader(const std::string fname, int type)
{
	GLuint vertShader = glCreateShader(type);
	MsgAssert(vertShader != 0, std::string("Error creating shader : ") + fname);

	const std::string shaderCode = LoadFileAsString(fname);
	const GLchar* codeArray[] = { shaderCode.c_str() };
	glShaderSource(vertShader, 1, codeArray, NULL);

	glCompileShader(vertShader);

	GLint result;
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
	if (GL_FALSE == result)
	{
		GLint logLen;
		glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char * log = new char[logLen];
			GLsizei written;
			glGetShaderInfoLog(vertShader, logLen, &written, log);
			std::cerr << "Shader log:\n" << log;
			delete[] log;
		}
		MsgAssert(false, "Shader compilation failed!");
	}

	return vertShader;
}

GLShader::GLShader(const std::string &fname, int type)
{
	shader_handle = LoadShader(fname, type);
	shader_file = fname;
}

GLuint GLShader::GetHandle() const
{
	return shader_handle;
}

GLProgram::GLProgram(std::vector<GLShader> &shaders)
{
	shader_list = shaders;
	program_handle = Compile(shader_list);
}

GLuint GLProgram::GetHandle() const
{
	return program_handle;
}

GLint GLProgram::GetUniformLocation(const std::string &name) const
{
	return glGetUniformLocation(program_handle, name.c_str());
}

void  GLProgram::SetUniform(const std::string &name, float value) const
{
	glUniform1f(GetUniformLocation(name), value);
}

void  GLProgram::SetUniform(const std::string &name, int value) const
{
	glUniform1i(GetUniformLocation(name), value);
}

void GLProgram::SetUniform(const std::string &name, glm::mat4 &value) const
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}

void GLProgram::SetUniform(const std::string &name, glm::vec4 &value) const
{
	glUniform4fv(GetUniformLocation(name), 1, &value[0]);
}

void GLProgram::SetUniform(const std::string &name, glm::vec3 &value) const
{
	glUniform3fv(GetUniformLocation(name), 1, &value[0]);
}

void GLProgram::SetUniform(const std::string &name, glm::vec2 &value) const
{
	glUniform2fv(GetUniformLocation(name), 1, &value[0]);
}

GLuint GLProgram::Compile(const std::vector<GLShader> &shaders)
{
	GLuint programHandle = glCreateProgram();
	MsgAssert(programHandle != 0, "Error creating shader program object");

	for (unsigned int cnt = 0; cnt < shaders.size(); cnt++)
	{
		glAttachShader(programHandle, shaders[cnt].GetHandle());
	}

	glLinkProgram(programHandle);

	GLint status;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
	if (GL_FALSE == status) {
		GLint logLen;
		glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH,
			&logLen);
		if (logLen > 0)
		{
			char * log = (char *)malloc(logLen);
			GLsizei written;
			glGetProgramInfoLog(programHandle, logLen,
				&written, log);
			fprintf(stderr, "Program log: \n%s", log);
			free(log);
		}
		MsgAssert(false, "Failed to link shader program!");
	}
	return programHandle;
}
