#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "GLIncludes.h"

enum GlTextureGenerator
{
	GL_TEXGEN_RANDOM,
	GL_TEXGEN_CHECKER
};

class GLTexture
{
protected:
	GLuint texture_id;
	GLuint width, height;
	GLbyte * raw_data;
	int channels;
	GLenum format, format_internal;

public:
	GLTexture();
	void GenerateTexture(GLuint width, GLuint height, GlTextureGenerator type = GL_TEXGEN_RANDOM);
	void GetTextureFromFile(std::string fname, GLenum format = 0);
	void LoadTextureToGPU();
	void Use(GLuint uniform_loc, GLuint texture_position = 0);
	~GLTexture();
};

#endif