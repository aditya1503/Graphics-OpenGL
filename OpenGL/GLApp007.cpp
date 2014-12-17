#include <iostream>

#include "GLUtils.h"
#include "GLShader.h"
#include "GLTransforms.h"
#include "GLVertexBuffer.h"
#include "GLTexture.h"
#include "GLApps.h"
#include "GLGeometry.h"

using namespace GLGeometry;

GLApp007::GLApp007() :
light_pos(5.0f, 5.0f, 0.0f),
light_col(1.0f, 1.0f, 0.6f, 1.0f),
mat_ambient(0.1f, 0.1f, 0.1f, 0.0f),
mat_diffuse(0.0f),
mat_specular(0.0f)
{
	
	InitScene();
	
}

void GLApp007::InitScene()
{
	vs2 = std::make_shared<GLShader>("transform.vs", GL_VERTEX_SHADER);
	ps2 = std::make_shared<GLShader>("wave.ps", GL_FRAGMENT_SHADER);
	vs = std::make_shared<GLShader>("lighting.vs", GL_VERTEX_SHADER);
	ps = std::make_shared<GLShader>("lighting.ps", GL_FRAGMENT_SHADER);
	prog = std::make_shared<GLProgram>(std::vector<GLShader>({ *vs, *ps }));
	prog2 = std::make_shared<GLProgram>(std::vector<GLShader>({ *vs, *ps }));
	prog3 = std::make_shared<GLProgram>(std::vector<GLShader>({ *vs, *ps }));
	progcl = std::make_shared<GLProgram>(std::vector<GLShader>({ *vs, *ps }));
	
	
	camera = std::make_shared<GLCamera>();
	camera2 = std::make_shared<GLCamera>();
	camera3 = std::make_shared<GLCamera>();

	texture = std::make_shared<GLTexture>();
	texture2 = std::make_shared<GLTexture>();
	texture3 = std::make_shared<GLTexture>();

	texturecl = std::make_shared<GLTexture>();

	enable_blend = false;
	enable_cloud = false;
	spherecl = GLGeometry::GenSphere(48, 48, 0, 1.0);

	vbuffercl = std::make_shared<GLVertexBuffer>(spherecl.numVertices());

	vbuffercl->AddElement(&spherecl.position[0], 3);
	vbuffercl->AddElement(&spherecl.normal[0], 3);
	vbuffercl->AddElement(&spherecl.color[0], 3);
	vbuffercl->AddElement(&spherecl.texcoord[0], 2);
	vbuffercl->GenBuffers();

	texturecl->GetTextureFromFile("cloud3.jpg", GL_BGR);
	texturecl->LoadTextureToGPU();
	glUseProgram(progcl->GetHandle());
	glBindVertexArray(vbuffercl->GetHandle());
	
	
	sphere = GLGeometry::GenSphere(48, 48,1,1.0);
	
	vbuffer = std::make_shared<GLVertexBuffer>(sphere.numVertices());

	vbuffer->AddElement(&sphere.position[0], 3);
	vbuffer->AddElement(&sphere.normal[0], 3);
	vbuffer->AddElement(&sphere.color[0], 3);
	vbuffer->AddElement(&sphere.texcoord[0], 2);
	vbuffer->GenBuffers();

	texture->GetTextureFromFile("sun.jpg", GL_BGR);
	texture->LoadTextureToGPU();
	
	glUseProgram(prog->GetHandle());
	glBindVertexArray(vbuffer->GetHandle());
	
	sphere2 = GLGeometry::GenSphere(48, 48, 0,1.0);

	vbuffer2 = std::make_shared<GLVertexBuffer>(sphere2.numVertices());

	vbuffer2->AddElement(&sphere2.position[0], 3);
	vbuffer2->AddElement(&sphere2.normal[0], 3);
	vbuffer2->AddElement(&sphere2.color[0], 3);
	vbuffer2->AddElement(&sphere2.texcoord[0], 2);
	vbuffer2->GenBuffers();

	texture2->GetTextureFromFile("earthn.jpg", GL_BGR);
	texture2->LoadTextureToGPU();

	glUseProgram(prog2->GetHandle());
	glBindVertexArray(vbuffer2->GetHandle());
	
	sphere3 = GLGeometry::GenSphere(48, 48, 0,1.0);

	vbuffer3 = std::make_shared<GLVertexBuffer>(sphere2.numVertices());

	vbuffer3->AddElement(&sphere3.position[0], 3);
	vbuffer3->AddElement(&sphere3.normal[0], 3);
	vbuffer3->AddElement(&sphere3.color[0], 3);
	vbuffer3->AddElement(&sphere3.texcoord[0], 2);
	vbuffer3->GenBuffers();
	
	texture3->GetTextureFromFile("earth.jpg", GL_BGR);
	texture3->LoadTextureToGPU();
	glUseProgram(prog3->GetHandle());
	glBindVertexArray(vbuffer3->GetHandle());


	progst = std::make_shared<GLProgram>(std::vector<GLShader>({ *vs, *ps }));
	camerast = std::make_shared<GLCamera>();
	texturest = std::make_shared<GLTexture>();

	spherest = GLGeometry::GenSphere(48, 48, 0, 100);

	vbufferst = std::make_shared<GLVertexBuffer>(spherest.numVertices());

	vbufferst->AddElement(&spherest.position[0], 3);
	vbufferst->AddElement(&spherest.normal[0], 3);
	vbufferst->AddElement(&spherest.color[0], 3);
	vbufferst->AddElement(&spherest.texcoord[0], 2);
	vbufferst->GenBuffers();

	texturest->GetTextureFromFile("stars3.jpg", GL_BGR);
	texturest->LoadTextureToGPU();

	glUseProgram(progst->GetHandle());
	glBindVertexArray(vbufferst->GetHandle());


	camerast->SetupView(glm::vec3(0.0f, 8.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));

	camera->SetupView(glm::vec3(0.0f, 8.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	camera2->SetupView(glm::vec3(0.0f, 8.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	camera3->SetupView(glm::vec3(0.0f, 2.0f, 6.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	GLMain::EnableDepthTest(true);
	GLMain::EnableBlend(false);
}

void GLApp007::RenderScene(double elapsedMilliseconds)
{
	GLMain::EnableBlend(false);

	//Overall settings
	glm::vec3 eye_posst = glm::vec3(-0.7, -3, 0.0f);
	light_pos = glm::vec3(glm::sin(time)*5.0f, glm::cos(time)*5.0f, 0.0f);
	camerast->PlaceAt(eye_posst);

	//Select Sphere Shaders and Vertex Data
	glUseProgram(progst->GetHandle());
	glBindVertexArray(vbufferst->GetHandle());

	//Set shader parameters
	progst->SetUniform("view_transform", camerast->GetTransform());
	progst->SetUniform("light_pos", light_pos);
	progst->SetUniform("eye_pos", eye_posst);
	progst->SetUniform("light_col", light_col);
	progst->SetUniform("mat_ambient", mat_ambient);
	progst->SetUniform("mat_diffuse", mat_diffuse);
	progst->SetUniform("mat_specular", mat_specular);
	texturest->Use(progst->GetUniformLocation("tex"));

	//Clear existing buffer and draw sphere
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, spherest.numVertices());

	//Clear existing buffer and draw sphere
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, spherest.numVertices());
	glm::vec3 eye_pos = glm::vec3(glm::sin(time / 2.0)*(8.0f), glm::cos(time / 2.0)*8.0f, 0.0f);
	light_pos = glm::vec3(glm::sin(time)*5.0f, glm::cos(time)*5.0f, 0.0f);
	
	glm::vec3 eye_pos2 = glm::vec3(glm::sin(time/2+1.6)*(-8.0f), glm::cos(time/2+1.6)*8.0f, 0.0f);
	glm::vec3 eye_posn = glm::vec3(glm::sin(time / 2 + 1.6)*(-8.0f), glm::cos(time / 2 + 1.6)*8.0f, 0.0f);
	glm::vec3 light_pos2 = glm::vec3(glm::sin(time-3.14159 )*5.0f, glm::cos(time-3.14159)*5.0f, 0.0f);
	glm::vec3 eye_pos3 = glm::vec3(glm::sin(time / 2.0+1.6)*(8.0f), glm::cos(time / 2.0+1.6)*8.0f, 0.0f);

	camera->PlaceAt(eye_pos);
	camera2->PlaceAt(eye_pos2);
	camera3->PlaceAt(eye_posn);

	//glEnable(GL_BLEND);
	//Select Sphere Shaders and Vertex Data
	GLMain::EnableBlend(false);

	glUseProgram(prog->GetHandle());
	glBindVertexArray(vbuffer->GetHandle());

	//Set shader parameters
	prog->SetUniform("view_transform", camera2->GetTransform());
	prog->SetUniform("light_pos", light_pos);
	prog->SetUniform("eye_pos", eye_pos);
	prog->SetUniform("light_col", light_col);
	prog->SetUniform("mat_ambient", mat_ambient);
	//prog->SetUniform("mat_diffuse", mat_diffuse);
	//prog->SetUniform("mat_specular", mat_specular);
	texture->Use(prog->GetUniformLocation("tex"));

	//Clear existing buffer and draw sphere*/
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, sphere.numVertices());
	
	GLMain::EnableBlend(false);

	
	glUseProgram(prog2->GetHandle());
	glBindVertexArray(vbuffer2->GetHandle());

	//Set shader parameters
	prog2->SetUniform("view_transform", camera->GetTransform());
	prog2->SetUniform("light_pos", light_pos2);
	prog2->SetUniform("eye_pos", eye_pos);
	prog2->SetUniform("light_col", light_col);
	prog2->SetUniform("mat_ambient", mat_ambient);
	prog2->SetUniform("mat_diffuse", mat_diffuse);
   // prog2->SetUniform("mat_specular", mat_specular);
	texture2->Use(prog->GetUniformLocation("tex"));

	//Clear existing buffer and draw sphere
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, sphere2.numVertices());
	GLMain::EnableBlend(enable_blend);

	glUseProgram(progcl->GetHandle());
	glBindVertexArray(vbuffercl->GetHandle());

	//Set shader parameters
	progcl->SetUniform("view_transform", camera->GetTransform());
	progcl->SetUniform("light_pos", light_pos);
	progcl->SetUniform("eye_pos", eye_pos);
	progcl->SetUniform("light_col", light_col);
	progcl->SetUniform("mat_ambient", mat_ambient);
	progcl->SetUniform("mat_diffuse", mat_diffuse);
	progcl->SetUniform("mat_specular", mat_specular);
	texturecl->Use(prog->GetUniformLocation("tex"));
	if (enable_cloud)
	glDrawArrays(GL_TRIANGLES, 0, spherecl.numVertices());
	GLMain::EnableBlend(enable_blend);


	glUseProgram(prog3->GetHandle());
	glBindVertexArray(vbuffer3->GetHandle());

	//Set shader parameters
	prog3->SetUniform("view_transform", camera->GetTransform());
	prog3->SetUniform("light_pos", light_pos);
	prog3->SetUniform("eye_pos", eye_pos);
	prog3->SetUniform("light_col", light_col);
	prog3->SetUniform("mat_ambient", mat_ambient);
	prog3->SetUniform("mat_diffuse", mat_diffuse);
	prog3->SetUniform("mat_specular", mat_specular);
	texture3->Use(prog->GetUniformLocation("tex"));

	
	glDrawArrays(GL_TRIANGLES, 0, sphere3.numVertices());

	//GLMain::EnableBlend(false);

	
	GLMain::EnableBlend(enable_blend);


	//Display result on screen
	glutSwapBuffers();
	glutPostRedisplay();

	//Increment elapsed time
	time += 0.0007f * (float)elapsedMilliseconds;
}

void GLApp007::HandleInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		running = false;
		break;
	case '1':
		mat_ambient += glm::vec4(0.05, 0.05, 0.05, 0.0);
		break;
	case '!':
		mat_ambient -= glm::vec4(0.05, 0.05, 0.05, 0.0);
		break;
	case '2':
		mat_diffuse += 0.1f;
		break;
	case '@':
		mat_diffuse -= 0.1f;
		break;
	case '3':
		mat_specular += 1.0f;
		break;
	case '#':
		mat_specular -= 1.0f;
		break;
	case '4':
		enable_blend = true;
		GLMain::EnableBlend(enable_blend);

		break;
		case '$':
			enable_blend = false;
		GLMain::EnableBlend(enable_blend);
		break;
		case '5':
			enable_cloud = true;
			printf("Cloud enabled\n");
			break;
		case '%':
			enable_cloud = false;
		break;

	}
}

void GLApp007::ResizeFunction(int width, int height)
{
	glViewport(0, 0, width, height);
	camera->SetupProjection(75.0f, static_cast<float>(width) / height, 0.001f, 1000.0f);
	camera2->SetupProjection(75.0f, static_cast<float>(width) / height, 0.001f, 1000.0f);
	camera3->SetupProjection(75.0f, static_cast<float>(width) / height, 0.001f, 1000.0f);
	camerast->SetupProjection(75.0f, static_cast<float>(width) / height, 0.001f, 1000.0f);

}