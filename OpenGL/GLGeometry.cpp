#include "GLGeometry.h"

#include <algorithm>

namespace GLGeometry
{
	void PushVertex3(std::vector<float> &geometry, float x, float y, float z = 0.0f)
	{
		geometry.push_back(x);
		geometry.push_back(y);
		geometry.push_back(z);
	}

	void PushVertex2(std::vector<float> &geometry, float x, float y)
	{
		geometry.push_back(x);
		geometry.push_back(y);
	}

	GLModel Gen2DMesh(int subdiv)
	{
		GLModel model;

		//Calculate positions of triangles
		float delta = 2.0f / subdiv;
		std::vector<float> &posdata = model.position;

		float x_offset = -1.0f, y_offset = -1.0f;
		for (int x = 0; x < subdiv; x++)
		{
			for (int y = 0; y < subdiv; y++)
			{
				PushVertex3(posdata, x_offset, y_offset);
				PushVertex3(posdata, x_offset + delta, y_offset);
				PushVertex3(posdata, x_offset, y_offset + delta);

				PushVertex3(posdata, x_offset, y_offset + delta);
				PushVertex3(posdata, x_offset + delta, y_offset);
				PushVertex3(posdata, x_offset + delta, y_offset + delta);

				y_offset += delta;
			}
			x_offset += delta;
			y_offset = -1.0f;
		}

		//Calculate color values for each position
		int count = subdiv*subdiv*6;
		std::vector<float> &colordata = model.color;
		int b_offset = count * 2 / 3;
		float reciprocal = 1.0f / count;

		for (int i = 0; i < count; i++)
		{
			colordata.push_back(i * reciprocal);
			colordata.push_back((count - i) * reciprocal);
			colordata.push_back(std::min(i, count - i) * reciprocal);
		}

		return model;
	}

	GLModel GenCylinder(int segments, int slices)
	{
		GLModel model;

		std::vector<float> &position = model.position;
		std::vector<float> &texcoord = model.texcoord;
		std::vector<float> &normal = model.normal;
		std::vector<float> &color = model.color;

		const float two_pi = 2.0f * 3.14159f;
		std::vector<float> data;

		float radius1 = 1.0f;
		float radius2 = 1.0f;

		for (int i = 0; i < segments; i++) //Vertical subdivisions
		{
			float z1 = (2.0f * i / segments) - 1.0f;
			float z2 = (2.0f * (i + 1) / segments) - 1.0f;

			for (int j = 0; j < slices; j++) //Radial subdivisions
			{
				float theta1 = two_pi * j / slices;
				float theta2 = two_pi * (j + 1) / slices;

				float x11 = radius1 * std::cosf(theta1);
				float x12 = radius1 * std::cosf(theta2);
				float x21 = radius2 * std::cosf(theta1);
				float x22 = radius2 * std::cosf(theta2);

				float y11 = radius1 * std::sinf(theta1);
				float y12 = radius1 * std::sinf(theta2);
				float y21 = radius2 * std::sinf(theta1);
				float y22 = radius2 * std::sinf(theta2);

				//Position data for sphere
				PushVertex3(position, x11, y11, z1);
				PushVertex3(position, x21, y21, z2);
				PushVertex3(position, x22, y22, z2);

				PushVertex3(position, x11, y11, z1);
				PushVertex3(position, x22, y22, z2);
				PushVertex3(position, x12, y12, z1);

				//Color data. just use |position| here...
				PushVertex3(color, fabs(x11), fabs(y11), fabs(z1));
				PushVertex3(color, fabs(x21), fabs(y21), fabs(z2));
				PushVertex3(color, fabs(x22), fabs(y22), fabs(z2));

				PushVertex3(color, fabs(x11), fabs(y11), fabs(z1));
				PushVertex3(color, fabs(x22), fabs(y22), fabs(z2));
				PushVertex3(color, fabs(x12), fabs(y12), fabs(z1));

				//Normal vectors, again same as position because this is a unit sphere.
				PushVertex3(normal, x11, y11, z1);
				PushVertex3(normal, x21, y21, z2);
				PushVertex3(normal, x22, y22, z2);

				PushVertex3(normal, x11, y11, z1);
				PushVertex3(normal, x22, y22, z2);
				PushVertex3(normal, x12, y12, z1);

				//Texture coordinates
				PushVertex2(texcoord, static_cast<float>(j) / slices, static_cast<float>(i) / segments);
				PushVertex2(texcoord, static_cast<float>(j) / slices, static_cast<float>(i + 1) / segments);
				PushVertex2(texcoord, static_cast<float>(j + 1) / slices, static_cast<float>(i + 1) / segments);

				PushVertex2(texcoord, static_cast<float>(j) / slices, static_cast<float>(i) / segments);
				PushVertex2(texcoord, static_cast<float>(j + 1) / slices, static_cast<float>(i + 1) / segments);
				PushVertex2(texcoord, static_cast<float>(j + 1) / slices, static_cast<float>(i) / segments);

			}
		}

		return model;
	}

	GLModel GenSphere(int segments, int slices,int flag,float radius)
	{
		GLModel model;

		
		std::vector<float> &position = model.position;
		std::vector<float> &texcoord = model.texcoord;
		std::vector<float> &normal = model.normal;
		std::vector<float> &color = model.color;
		

		//Unit sphere centered at zero
		const float two_pi = 2.0f * 3.14159f;
		std::vector<float> data;
		for (int i = 0; i < segments; i++) //Vertical subdivisions
		{
			float z1 = (2.0f * i / segments) - 1.0f;
			float z2 = (2.0f * (i+1) / segments) - 1.0f;

			float radius1 = std::sqrt(radius - z1*z1);
			float radius2 = std::sqrt(radius - z2*z2);
			
			for (int j = 0; j < slices; j++) //Radial subdivisions
			{
				float theta1 = two_pi * j / slices;
				float theta2 = two_pi * (j + 1) / slices;

				float x11 = radius1 * std::cosf(theta1);
				float x12 = radius1 * std::cosf(theta2);
				float x21 = radius2 * std::cosf(theta1);
				float x22 = radius2 * std::cosf(theta2);

				float y11 = radius1 * std::sinf(theta1);
				float y12 = radius1 * std::sinf(theta2);
				float y21 = radius2 * std::sinf(theta1);
				float y22 = radius2 * std::sinf(theta2);

				//Position data for sphere
				PushVertex3(position,x11, y11, z1);
				PushVertex3(position, x21, y21, z2);
				PushVertex3(position, x22, y22, z2);

				PushVertex3(position, x11, y11, z1);
				PushVertex3(position, x22, y22, z2);
				PushVertex3(position, x12, y12, z1);

				//Color data. just use |position| here...
				PushVertex3(color, fabs(x11), fabs(y11), fabs(z1));
				PushVertex3(color, fabs(x21), fabs(y21), fabs(z2));
				PushVertex3(color, fabs(x22), fabs(y22), fabs(z2));

				PushVertex3(color, fabs(x11), fabs(y11), fabs(z1));
				PushVertex3(color, fabs(x22), fabs(y22), fabs(z2));
				PushVertex3(color, fabs(x12), fabs(y12), fabs(z1));

				//Normal vectors, again same as position because this is a unit sphere.
				PushVertex3(normal, x11, y11, z1);
				PushVertex3(normal, x21, y21, z2);
				PushVertex3(normal, x22, y22, z2);

				PushVertex3(normal, x11, y11, z1);
				PushVertex3(normal, x22, y22, z2);
				PushVertex3(normal, x12, y12, z1);

				//Texture coordinates
				PushVertex2(texcoord, static_cast<float>(j) / slices, static_cast<float>(i) / segments);
				PushVertex2(texcoord, static_cast<float>(j) / slices, static_cast<float>(i+1) / segments);
				PushVertex2(texcoord, static_cast<float>(j+1) / slices, static_cast<float>(i+1) / segments);

				PushVertex2(texcoord, static_cast<float>(j) / slices, static_cast<float>(i) / segments);
				PushVertex2(texcoord, static_cast<float>(j+1) / slices, static_cast<float>(i+1) / segments);
				PushVertex2(texcoord, static_cast<float>(j+1) / slices, static_cast<float>(i) / segments);

			}
		}
		if (flag==1)
		for (int i = 0; i < model.position.size(); i+=3){
			position[i] -= 5.0;
		}

		return model;
	}
}
