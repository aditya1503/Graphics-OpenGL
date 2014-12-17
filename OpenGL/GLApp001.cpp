#include <iostream>

#include "GLUtils.h"
#include "GLShader.h"
#include "GLVertexBuffer.h"
#include "GLApps.h"

GLApp001::GLApp001()
{
	InitScene();
}

void GLApp001::InitScene()
{
	vs		= std::make_shared<GLShader>("basic.vs", GL_VERTEX_SHADER);
	ps		= std::make_shared<GLShader>("basic.ps", GL_FRAGMENT_SHADER);
	prog	= std::make_shared<GLProgram>(std::vector<GLShader>({ *vs, *ps }));
	vbuffer = std::make_shared<GLVertexBuffer>(3);

	float positionData[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,		
		1.0f,0.0f, 0.0f
	};

	float colorData[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f	
	};

	vbuffer->AddElement(positionData, 3);
	vbuffer->AddElement(colorData, 3);
	vbuffer->GenBuffers();

	glUseProgram(prog->GetHandle());
	glBindVertexArray(vbuffer->GetHandle());
}

void GLApp001::RenderScene(double elapsedMilliseconds)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
	glutPostRedisplay();
}
