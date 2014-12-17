#version 400
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexNormal;
layout(location = 2) in vec3 VertexColor;
layout(location = 3) in vec2 VertexTexcoord;

out vec4 world_pos;
out vec3 world_normal;
out vec3 color;
out vec2 texcoord;

uniform mat4 world_transform = mat4(1.0); //Initialize this to an identity matrix (constructor input is used to set the diagonal elements)
uniform mat4 view_transform = mat4(1.0);

void main()
{
	//First apply world transformation on the position and store separately.
	//We do this because it is more intuitive to do lighting in world coordinates than final view coordinates.
	world_pos	= world_transform * vec4(VertexPosition,1.0);

	//Normal vectors are transformed slightly differently from position because you can't Translate an normal.
	//To use a regular 4x4 transform matrix on a 3d direction vector (like the normal), we convert the normal...
	//into a 4d vector with w = 0.0. This will take care of discarding any translation in the 4x4 transform matrix.
	world_normal= (world_transform * vec4(VertexNormal, 0.0)).xyz;

	//These 2 components are passed through without modification. No need to transform these.
	color		= VertexColor;
	texcoord	= VertexTexcoord;
	
	//Final view position is obtained by applying projection transform on the world_position.
	gl_Position = view_transform * world_pos;
}