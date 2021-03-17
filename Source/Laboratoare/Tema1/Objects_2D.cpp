#include "Objects_2D.h"
#include <iostream>
#include <cmath>
#include <Core/Engine.h>
using namespace std;



Mesh* Objects_2D::CreateShuriken(std::string name, glm::vec3 center, float shuriken_side, glm::vec3 color, bool fill)
{
	glm::vec3 corner = center;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(shuriken_side, 0, 0), color),
		VertexFormat(corner + glm::vec3(shuriken_side, shuriken_side, 0), color),
		VertexFormat(corner + glm::vec3(0, shuriken_side, 0), color),
		VertexFormat(corner + glm::vec3(-shuriken_side, shuriken_side, 0), color),
		VertexFormat(corner + glm::vec3(-shuriken_side, 0, 0), color),
		VertexFormat(corner + glm::vec3(-shuriken_side, -shuriken_side, 0), color),
		VertexFormat(corner + glm::vec3(0, -shuriken_side, 0), color),
		VertexFormat(corner + glm::vec3(shuriken_side, -shuriken_side, 0), color),

	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 
											0, 3, 4,
											0, 5, 6,
											0, 7, 8};

	if (fill != false) {
		triangle->SetDrawMode(GL_TRIANGLES);
	}

	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* Objects_2D::CreateTriangle(std::string name, glm::vec3 up_corner, float triangle_side, glm::vec3 color, bool fill)
{

	glm::vec3 corner = up_corner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(triangle_side, 0, 0), color),
		VertexFormat(corner + glm::vec3(0, triangle_side, 0), color),
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = {0, 1, 2};

	if (fill != false) {
		triangle->SetDrawMode(GL_TRIANGLES);
	}

	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* Objects_2D::CreateRectangle(std::string name, glm::vec3 left_down_corner, float rectangle_height, float rectangle_width, glm::vec3 color, bool fill)
{

	glm::vec3 corner = left_down_corner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(rectangle_width, 0, 0), color),
		VertexFormat(corner + glm::vec3(rectangle_width, rectangle_height, 0), color),
		VertexFormat(corner + glm::vec3(0, rectangle_height, 0), color),
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 3,
										    1, 3, 2};

	if (fill != false) {
		rectangle->SetDrawMode(GL_TRIANGLES);
	}

	rectangle->InitFromData(vertices, indices);
	return rectangle;
}

Mesh* Objects_2D::CreateArrow(std::string name, glm::vec3 rectangle_corner, float rectangle_height, float rectangle_width, float triangle_side, glm::vec3 color, bool fill)
{
	glm::vec3 corner = rectangle_corner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(-triangle_side * 1.73 / 2, triangle_side / 2, 0), color),
		VertexFormat(corner + glm::vec3(-triangle_side * 1.73 / 2, rectangle_height / 2, 0), color),
		VertexFormat(corner + glm::vec3(-triangle_side * 1.73 / 2 - rectangle_width, rectangle_height / 2, 0), color),
		VertexFormat(corner + glm::vec3(-triangle_side * 1.73 / 2 - rectangle_width, -rectangle_height / 2, 0), color),
		VertexFormat(corner + glm::vec3(-triangle_side * 1.73 / 2, -rectangle_height / 2, 0), color),
		VertexFormat(corner + glm::vec3(-triangle_side * 1.73 / 2, -triangle_side / 2, 0), color),
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = {0, 1, 6,
										   2, 4, 3, 
										   4, 5, 2};

	if (fill != false) {
		triangle->SetDrawMode(GL_TRIANGLES);
	}

	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* Objects_2D::CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill)
{
	glm::vec3 corner = center;

	int num_segments = 500;

	std::vector<VertexFormat> vertices = {};

	for(int i = 0; i < 360; i++) {
		float theta = M_PI * float(i) / 180;
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);
		//cout << "x: " << x << "     y: " << y << endl;
		vertices.push_back(VertexFormat(corner + glm::vec3(x, y, 0), color));
	}

	Mesh* circle = new Mesh(name);
	std::vector<unsigned short> indices = {};
	int counter = 1;
	for (int i = 0; i < 2 * num_segments - 1; i++) {
		if (i % 2 == 0) {
			indices.push_back(0);
			indices.push_back(counter);
		}
		else {
			counter++;
			indices.push_back(counter);
		}
	}

	if (fill != false) {
		circle->SetDrawMode(GL_TRIANGLE_FAN);
	}

	circle->InitFromData(vertices, indices);
	return circle;
}

Mesh* Objects_2D::CreatePolyline(std::string name, glm::vec3 center, float width_factor, float height_factor, glm::vec3 color, bool fill)
{
	glm::vec3 corner = center;
	int number_of_lines = 4;
	int number_of_points = 9;

	std::vector<VertexFormat> vertices = { VertexFormat(corner, color) };
	
	/*	VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(-width_factor, 0, 0), color),*/
	float depth = -height_factor;
	for (int i = 0; i < number_of_lines; i++) {
		vertices.push_back(VertexFormat(corner + glm::vec3(-width_factor, depth, 0), color));
		width_factor *= 0.9;
		height_factor *= 0.9;
		depth -= height_factor;
		vertices.push_back(VertexFormat(corner + glm::vec3(width_factor, depth, 0), color));
	}

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = {};

	for (int i = 0; i < number_of_points; i++) {
		indices.push_back(i);
		if(i < number_of_points - 2)
			indices.push_back(i + 1);
	}

	if (fill != false) {
		triangle->SetDrawMode(GL_LINES);
	}

	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* Objects_2D::CreateBow(std::string name, glm::vec3 center, float arch_radius, glm::vec3 color, bool fill)
{
	glm::vec3 corner = center;

	int num_of_vertices = 0;

	std::vector<VertexFormat> vertices = {};

	for (int i = 0; i < 2000; i++) {
		float theta = M_PI * float(i) / 100;
		float x = arch_radius * cosf(theta);
		float y = arch_radius * sinf(theta);
		if (x >= 0 && x <= arch_radius) {
			//cout << "x: " << x << "     y: " << y << endl;
			vertices.push_back(VertexFormat(corner + glm::vec3(x, y, 0), color));
			num_of_vertices++;
		}
	}

	Mesh* circle = new Mesh(name);
	std::vector<unsigned short> indices = {};
	int counter = 1;
	for (int i = 0; i < num_of_vertices; i++) {
			indices.push_back(i);
	}

	if (fill != false) {
		circle->SetDrawMode(GL_LINES);
	}

	circle->InitFromData(vertices, indices);
	return circle;
}
