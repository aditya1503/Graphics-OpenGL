#version 400
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexColor;
out vec3 Color;

uniform mat4 transform;
uniform float phase = 0.0;
uniform float displacement = 0.1;

void main()
{
	Color = VertexColor;
	vec3 delta_z = vec3(0.0,0.0,sin(4.0 * (VertexPosition.x + phase)) + cos(4.0 * (VertexPosition.y + phase))) * displacement;
	gl_Position = transform * vec4(VertexPosition + delta_z,1.0);
}