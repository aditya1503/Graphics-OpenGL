#include <iostream>

#include "GLUtils.h"
#include "GLIncludes.h"
#include "GLApps.h"

SimpleGLApp::SimpleGLApp()
{
	running = true;
	time = 0.0f;
}

bool SimpleGLApp::Running() const
{
	return running;
}

void SimpleGLApp::HandleInput(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		running = false;
	}
}

void SimpleGLApp::ResizeFunction(int width, int height)
{
	glViewport(0, 0, width, height);
}