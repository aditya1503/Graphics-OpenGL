#include "GLTexture.h"
#include "GLUtils.h"
#include "FreeImage.h"

GLTexture::GLTexture()
{
	texture_id = GL_INVALID_VALUE;	//OpenGL texture handle
	raw_data = NULL;	//CPU buffer that contains the actual texture data that is loaded to GPU.
	channels = 3;		//Number of components in image. RGBA (Red, Green, Blue, Alpha) is 4, RGB is 3.
	format = format_internal = GL_RGB;
}

void GLTexture::GetTextureFromFile(std::string fname, GLenum format)
{	
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;//image format	
	FIBITMAP *dib(0);					//pointer to the image, once loaded	

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(fname.c_str(), 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(fname.c_str());
	//if still unkown, return failure
	MsgAssert((fif != FIF_UNKNOWN), "Unknown texture file format");

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, fname.c_str());
	//if the image failed to load, return failure
	MsgAssert((dib != 0), "Unable to load texture file");

	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	//calculate number of channels (works only for 8 bit channels)
	channels = FreeImage_GetLine(dib) / FreeImage_GetWidth(dib);

	//retrieve the image data
	raw_data = new GLbyte[width*height*channels];
	BYTE * src = FreeImage_GetBits(dib);
	memcpy(raw_data, src, width*height*channels);

	//if this somehow one of these failed (they shouldn't), return failure
	MsgAssert(((raw_data != 0) && (width != 0) && (height != 0)), "Unable to load texture file");

	//Set texture format and perform swizzling (reodering of RGB) if required 
	format_internal = (channels == 3) ? GL_RGB : GL_RGBA;
	this->format = (format == 0) ? format_internal : format;

	FreeImage_Unload(dib);
}

void GLTexture::GenerateTexture(GLuint width, GLuint height, GlTextureGenerator type)
{
	this->width = width;
	this->height = height;
	
	channels = 4;
	format = format_internal = GL_RGBA;

	if (raw_data != NULL) { delete[] raw_data; }
	raw_data = new GLbyte[width * height * 4]; //4 bytes per pixel because of RGBA (one byte each)
	GLuint * dwordptr = reinterpret_cast<GLuint*>(raw_data); //fill data 4 bytes at a time

	switch (type)
	{
	case GL_TEXGEN_CHECKER:
		//Create a checker board pattern with every 4x4 pixels being either black or white.
		for (uint32_t i = 0; i < width * height; i++)
		{
			int row = (i / height) % 8;
			int col = (i % width) % 8;
			dwordptr[i] = ((row < 4 && col < 4) || (row >= 4 && col >= 4)) ? 0xffffffff : 0x0;
		}
		break;
	case GL_TEXGEN_RANDOM:
		//Random RGBA values
		for (uint32_t i = 0; i < width * height; i++)
		{
			float randval = static_cast<float>(rand()) / RAND_MAX;
			dwordptr[i] = static_cast<GLuint>(0xFFFFFFFF * randval);
		}		
		break;
	}
}

void GLTexture::LoadTextureToGPU()
{	
	MsgAssert((channels == 3 || channels == 4), "Unsupported number of channels in image");	
	
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_LINEAR or GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //GL_CLAMP_TO_EDGE or GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, format_internal, width, height, 0, format, GL_UNSIGNED_BYTE, raw_data);
}

void GLTexture::Use(GLuint uniform_loc, GLuint texture_position)
{
	GLuint uniform_mytexture = 0;
	glActiveTexture(GL_TEXTURE0 + texture_position);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glUniform1i(uniform_loc, texture_position);	
}

GLTexture::~GLTexture()
{
	if (texture_id != GL_INVALID_VALUE)
	{
		glDeleteTextures(1, &texture_id);
	}

	if (raw_data != NULL)
	{
		delete[] raw_data;
	}
}