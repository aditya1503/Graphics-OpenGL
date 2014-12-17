#include <iostream>

#include "GLUtils.h"
#include "GLShader.h"
#include "GLTransforms.h"
#include "GLVertexBuffer.h"
#include "GLApps.h"

GLApp002::GLApp002()
{
	InitScene();
}

void GLApp002::InitScene()
{
	vs = std::make_shared<GLShader>("transform.vs", GL_VERTEX_SHADER);
	ps = std::make_shared<GLShader>("basic.ps", GL_FRAGMENT_SHADER);
	prog = std::make_shared<GLProgram>(std::vector<GLShader>({ *vs, *ps }));
	vbuffer = std::make_shared<GLVertexBuffer>(4);

	camera = std::make_shared<GLCamera>();

	float positionData[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		-1.0f, 0.0f, 0.0f
	};

	float colorData[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f
	};

	vbuffer->AddElement(positionData, 3);
	vbuffer->AddElement(colorData, 3);
	vbuffer->GenBuffers();

	glUseProgram(prog->GetHandle());
	glBindVertexArray(vbuffer->GetHandle());
	
	camera->SetupView(glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
}

void GLApp002::RenderScene(double elapsedMilliseconds)
{
	camera->PlaceAt(glm::vec3(glm::sin(time)*4.0f, glm::cos(time)*4.0f, 1.0f));
	prog->SetUniform("transform", camera->GetTransform());
	time += 0.001f * (float)elapsedMilliseconds;
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glutSwapBuffers();
	glutPostRedisplay();
}

void GLApp002::ResizeFunction(int width, int height)
{
	glViewport(0, 0, width, height);
	camera->SetupProjection(75.0f, static_cast<float>(width) / height, 0.001f, 1000.0f);
}