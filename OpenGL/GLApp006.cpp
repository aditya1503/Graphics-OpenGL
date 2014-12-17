#include <iostream>

#include "GLUtils.h"
#include "GLShader.h"
#include "GLTransforms.h"
#include "GLVertexBuffer.h"
#include "GLTexture.h"
#include "GLApps.h"
#include "GLGeometry.h"

using namespace GLGeometry;

GLApp006::GLApp006()
{
	InitScene();
}

void GLApp006::InitScene()
{
	//Load texture shaders
	vs = std::make_shared<GLShader>("texture.vs", GL_VERTEX_SHADER);
	ps = std::make_shared<GLShader>("texture.ps", GL_FRAGMENT_SHADER);
	prog = std::make_shared<GLProgram>(std::vector<GLShader>({ *vs, *ps }));

	//Load basic color shaders
	vs2 = std::make_shared<GLShader>("transform.vs", GL_VERTEX_SHADER);
	ps2 = std::make_shared<GLShader>("wave.ps", GL_FRAGMENT_SHADER);
	prog2 = std::make_shared<GLProgram>(std::vector<GLShader>({ *vs2, *ps2 }));

	camera = std::make_shared<GLCamera>();
	texture = std::make_shared<GLTexture>();
	
	numVertices = 4;

	enable_blend = false;

	//Create first (textured) rectangle:
	vbuffer = std::make_shared<GLVertexBuffer>(numVertices);

	float positionData[] = {
		1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		0.0f, -1.0f, 1.0f,
		-1.0f, 0.0f, 1.0f
	};

	float texData[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	vbuffer->AddElement(positionData, 3);
	vbuffer->AddElement(texData, 2);
	vbuffer->GenBuffers();
	
	//Create second rectangle (plain color):
	vbuffer2 = std::make_shared<GLVertexBuffer>(numVertices);
	float positionData2[] = {
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

	vbuffer2->AddElement(positionData2, 3);
	vbuffer2->AddElement(colorData, 3);
	vbuffer2->GenBuffers();

	//Load texture
	texture->GetTextureFromFile("bird.png", GL_BGRA);
	texture->LoadTextureToGPU();

	camera->SetupView(glm::vec3(0.0f,2.0f,6.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	GLMain::EnableDepthTest(true);
}

void GLApp006::RenderScene(double elapsedMilliseconds)
{
	//View point
	glm::vec3 eye_pos = glm::vec3(glm::sin(time / 2.0)*2.0f, glm::cos(time / 2.0)*2.0f, 6.0f);	
	camera->PlaceAt(eye_pos);
	
	//Clear existing buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Select basic shaders and colored object, and draw it
	glUseProgram(prog2->GetHandle());
	glBindVertexArray(vbuffer2->GetHandle());		
	prog2->SetUniform("transform", camera->GetTransform());
	prog2->SetUniform("color_phase", time);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, numVertices);

	//Select texture shaders and textured object, and draw it
	glUseProgram(prog->GetHandle());
	glBindVertexArray(vbuffer->GetHandle());
	prog->SetUniform("transform", camera->GetTransform());
	texture->Use(prog->GetUniformLocation("tex"));
	glDrawArrays(GL_TRIANGLE_STRIP, 0, numVertices);
		
	//Display result on screen
	glutSwapBuffers();
	glutPostRedisplay();

	//Increment elapsed time
	time += 0.001f * (float)elapsedMilliseconds;
}

void GLApp006::HandleInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		running = false;
		break;
	case '1':
		enable_blend = !enable_blend;
		GLMain::EnableDepthTest(!enable_blend);
		GLMain::EnableBlend(enable_blend);
		break;
	}
}

void GLApp006::ResizeFunction(int width, int height)
{
	glViewport(0, 0, width, height);
	camera->SetupProjection(75.0f, static_cast<float>(width) / height, 0.001f, 1000.0f);
}