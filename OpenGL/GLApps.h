#ifndef GLAPPS_H
#define GLAPPS_H

#include <memory>
#include "GLMain.h"
#include <glm/glm.hpp>
#include "GLGeometry.h"

class GLShader;
class GLProgram;
class GLVertexBuffer;
class GLTexture;
class GLCamera;

class SimpleGLApp : public GLApplication
{
protected:
	std::shared_ptr<GLShader> vs,vs2,vsst;
	std::shared_ptr<GLShader> ps,ps2,psst;
	std::shared_ptr<GLProgram> prog,prog2,prog3,progcl,progan,progst;
	std::shared_ptr<GLVertexBuffer> vbuffer,vbuffer2,vbuffer3,vbuffercl,vbufferan,vbufferst;
	float time;
	bool running;
public:
	SimpleGLApp();
	bool Running() const;
	virtual void HandleInput(unsigned char key, int x, int y);
	virtual void ResizeFunction(int width, int height);
};

class GLApp001 : public SimpleGLApp
{
public:
	GLApp001();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
};

class GLApp002 : public SimpleGLApp
{
protected:
	std::shared_ptr<GLCamera> camera;
public:
	GLApp002();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
	void ResizeFunction(int width, int height);
};

class GLApp003 : public SimpleGLApp
{
protected:
	int num_vertices;
	bool animating, rotating;
	float displacement;
	std::shared_ptr<GLCamera> camera;
public:
	GLApp003();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
	void HandleInput(unsigned char key, int x, int y);
	void ResizeFunction(int width, int height);
};

class GLApp004 : public SimpleGLApp
{
protected:
	std::shared_ptr<GLTexture> texture;
	std::shared_ptr<GLCamera> camera;
public:
	GLApp004();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
	void ResizeFunction(int width, int height);
};

class GLApp005 : public SimpleGLApp
{
protected:
	std::shared_ptr<GLTexture> texturest;
	std::shared_ptr<GLCamera> camerast;
public:
	GLApp005();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
	void ResizeFunction(int width, int height);
};

class GLApp006 : public SimpleGLApp
{
protected:
	int numVertices;
	std::shared_ptr<GLCamera> camera;
	std::shared_ptr<GLTexture> texture;

	std::shared_ptr<GLShader> vs2;
	std::shared_ptr<GLShader> ps2;
	std::shared_ptr<GLProgram> prog2;
	std::shared_ptr<GLVertexBuffer> vbuffer2;

	bool enable_blend;

public:
	GLApp006();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
	void HandleInput(unsigned char key, int x, int y);
	void ResizeFunction(int width, int height);
};

class GLApp007 : public SimpleGLApp
{
protected:
	std::shared_ptr<GLCamera> camera,camera1,camera2,camera3,camerast;
	std::shared_ptr<GLTexture> texture,texture2,texture3,texturecl,texturest;
	bool enable_blend,enable_cloud;
	GLGeometry::GLModel sphere,sphere2,sphere3,spherecl,spherest;
	std::shared_ptr<GLVertexBuffer> vbuffer;
	glm::vec3 light_pos;
	glm::vec4 light_col, mat_ambient;
	float mat_diffuse, mat_specular;

public:
	GLApp007();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
	void HandleInput(unsigned char key, int x, int y);
	void ResizeFunction(int width, int height);
};


#endif