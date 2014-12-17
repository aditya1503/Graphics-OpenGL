#ifndef GLGEOMETRY_H
#define GLGEOMETRY_H

#include <vector>

namespace GLGeometry
{
	struct GLModel
	{
		std::vector<float> position;
		std::vector<float> color;
		std::vector<float> texcoord;
		std::vector<float> normal;

		int numVertices()
		{
			return position.size() / 3;
		}
	};

	GLModel Gen2DMesh(int subdiv);
	GLModel GenSphere(int segments, int slices,int flag,float radius);
	GLModel GenCylinder(int segments, int slices);
}

#endif