#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Objects_2D
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateShuriken(std::string name, glm::vec3 center, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateTriangle(std::string name, glm::vec3 corner, float triangle_side, glm::vec3 color, bool fill);
	Mesh* CreateRectangle(std::string name, glm::vec3 left_down_corner, float rectangle_height, float rectangle_width, glm::vec3 color, bool fill);
	Mesh* CreateArrow(std::string name, glm::vec3 corner, float rectangle_height, float rectangle_width,
					  float triangle_side, glm::vec3 color, bool fill);
	Mesh* CreateCircle(std::string name, glm::vec3 center, float radius, glm::vec3 color, bool fill);
	Mesh* CreatePolyline(std::string name, glm::vec3 center, float width_factor, float height_factor, glm::vec3 color, bool fill);
	Mesh* CreateBow(std::string name, glm::vec3 center, float arch_width, glm::vec3 color, bool fill);

}
