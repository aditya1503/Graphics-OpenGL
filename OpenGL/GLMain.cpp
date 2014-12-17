#include <iostream>

#include "GLIncludes.h"
#include "GLUtils.h"
#include "GLMain.h"

//Initialize static members
double GLMain::elapsedMilliseconds		= 0.0;
bool GLMain::initialized_glut			= false;
GLApplication * GLMain::current_context = NULL;

void GLMain::RenderCallback()
{
	MsgAssert(current_context != NULL, "Please bind a GLMain object first");
	current_context->RenderScene(elapsedMilliseconds);
}

void GLMain::InputCallback(unsigned char key, int x, int y)
{
	MsgAssert(current_context != NULL, "Please bind a GLMain object first");
	current_context->HandleInput(key,x,y);
}

void GLMain::ResizeCallback(int width, int height)
{
	MsgAssert(current_context != NULL, "Please bind a GLMain object first");
	current_context->ResizeFunction(width,height);
}

void GLMain::Run(GLApplication &p)
{
	current_context = &p;

	int loop_count = 0;
	PerformanceCounter fps_counter,frame_counter;

	while (current_context->Running())
	{	
		elapsedMilliseconds = frame_counter.GetTimeMilliSeconds();
		frame_counter.Start();

		glutMainLoopEvent();

		loop_count++;
		if (loop_count == 1024) 
		{
			std::cout << "FPS = " << loop_count / fps_counter.GetTimeSeconds() << std::endl;
			fps_counter.Start();
			loop_count = 0;
		}
	}
}

void GLMain::InitializeGLUT()
{
	MsgAssert(!initialized_glut, "Cannot create two instances of GLMain");

	initialized_glut = true;
	int argc = 1;
	char *dummyArgs = "appname";

	// init GLUT and create Window
	glutInit(&argc, &dummyArgs);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("OpenGL Test");

	GLenum retval = glewInit();
	MsgAssert(retval == GLEW_OK, "Error initializing GLEW");

	CheckDeviceCaps();

	// register callbacks
	glutDisplayFunc(RenderCallback);
	glutKeyboardFunc(InputCallback);
	glutReshapeFunc(ResizeCallback);

	glEnable(GL_MULTISAMPLE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //default blend
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
}

void GLMain::EnableDepthTest(bool value)
{
	if (value)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}
}

void GLMain::EnableBlend(bool value)
{
	if (value)
	{
		glEnable(GL_BLEND);
	}
	else
	{
		glDisable(GL_BLEND);
	}
}

bool GLMain::Initialized()
{
	return initialized_glut;
}

void GLMain::CheckDeviceCaps()
{
	MsgAssert(GLEW_ARB_vertex_program != 0, "Vertex Shaders not supported!");
}

GLApplication::GLApplication()
{
	MsgAssert(GLMain::Initialized(), "Call GLMain::InitializeGLUT() before creating GLApplications");
}


