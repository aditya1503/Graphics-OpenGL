#version 400
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 texInput;
out vec2 texcoord;

uniform mat4 transform;

void main()
{
	texcoord = texInput;
	gl_Position = transform * vec4(VertexPosition,1.0);
}