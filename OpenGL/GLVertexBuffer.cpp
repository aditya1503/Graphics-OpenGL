#include "GLVertexBuffer.h"
#include "GLUtils.h"

GLuint GLVertexBuffer::GetHandle() const
{
	return buffer_handle;
}
int GLVertexBuffer::Count() const
{
	return num_vertices;
}

void GLVertexBuffer::AddElement(float * data, int components)
{
	MsgAssert(buffer_handle == 0, "Cannot add elements after buffer is created");
	element_data.push_back(data);
	element_num_components.push_back(components);
}

GLVertexBuffer::GLVertexBuffer(int numVertices)
{
	num_vertices = numVertices;
	buffer_handle = 0;
}

void GLVertexBuffer::GenBuffers()
{
	MsgAssert(element_handles.size() == 0, "Cannot handle reassignment yet");

	// Create the buffer objects
	GLsizei numBuffers = element_data.size();
	GLuint *vboHandles = new GLuint[numBuffers];
	glGenBuffers(numBuffers, vboHandles);
	element_handles.clear();
	element_handles.assign(vboHandles,vboHandles + numBuffers);
	delete[] vboHandles;

	// Populate each buffer
	for (int i = 0; i < numBuffers; i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, element_handles[i]);
		glBufferData(GL_ARRAY_BUFFER, element_num_components[i] * num_vertices * sizeof(float), element_data[i], GL_STATIC_DRAW);
	}

	glGenVertexArrays(1, &buffer_handle);
	glBindVertexArray(buffer_handle);

	// Enable the vertex attribute arrays and map indices
	for (int i = 0; i < numBuffers; i++)
	{
		glEnableVertexAttribArray(i);
		glBindBuffer(GL_ARRAY_BUFFER, element_handles[i]);
		glVertexAttribPointer(i, element_num_components[i], GL_FLOAT, GL_FALSE, 0, (GLubyte *)0);
	}
}
