#include <iostream>

#include "GLUtils.h"
#include "GLShader.h"
#include "GLTransforms.h"
#include "GLVertexBuffer.h"
#include "GLTexture.h"
#include "GLApps.h"

GLApp005::GLApp005()
{
	InitScene();
}

void GLApp005::InitScene()
{
	vsst = std::make_shared<GLShader>("texture.vs", GL_VERTEX_SHADER);
	psst = std::make_shared<GLShader>("texture.ps", GL_FRAGMENT_SHADER);
	progst = std::make_shared<GLProgram>(std::vector<GLShader>({ *vsst, *psst }));
	vbufferst = std::make_shared<GLVertexBuffer>(4);
	texturest = std::make_shared<GLTexture>();

	camerast = std::make_shared<GLCamera>();

	float positionData[] = {
		30.0f, 0.0f,-40.0f,
		0.0f, 30.0f, -40.0f,
		0.0f, -30.0f, -40.0f,
		-30.0f, 0.0f, -40.0f
	};

	float texData[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	vbufferst->AddElement(positionData, 3);
	vbufferst->AddElement(texData, 2);
	vbufferst->GenBuffers();

	glUseProgram(progst->GetHandle());
	glBindVertexArray(vbufferst->GetHandle());

	camerast->SetupView(glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	//texture->GenerateTexture(16,16,GL_TEXGEN_CHECKER);
	texturest->GetTextureFromFile("stars2.jpg", GL_BGR);
	texturest->LoadTextureToGPU();

	GLMain::EnableDepthTest(true);
}

void GLApp005::RenderScene(double elapsedMilliseconds)
{
	//GLMain::EnableDepthTest(false);

	camerast->PlaceAt(glm::vec3(0,1,20));
	progst->SetUniform("transform", camerast->GetTransform());
	texturest->Use(progst->GetUniformLocation("tex"));
	time += 0.001f * (float)elapsedMilliseconds;
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	GLMain::EnableDepthTest(true);

	glutSwapBuffers();
	glutPostRedisplay();
}

void GLApp005::ResizeFunction(int width, int height)
{
	glViewport(0, 0, width, height);
	camerast->SetupProjection(75.0f, static_cast<float>(width) / height, -100, 1000.0f);
}