#ifndef GLVERTEXBUFFER_H
#define GLVERTEXBUFFER_H

#include "GLIncludes.h"
#include <vector>

class GLVertexBuffer
{
protected:
	GLuint buffer_handle;
	int num_vertices;

	std::vector<GLuint> element_handles;
	std::vector<float*> element_data;
	std::vector<int> element_num_components;

public:
	GLVertexBuffer(int numVertices);
	GLuint GetHandle() const;
	int Count() const;
	void AddElement(float * elem_data, int components);
	void GenBuffers();
};

#endif