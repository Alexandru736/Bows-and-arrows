#include "Tema1.h"

#include <vector>
#include <iostream>
#include <random>

#include <Core/Engine.h>

#include "Laboratoare\Laborator3\Transform2D.h"
#include "Objects_2D.h"

using namespace std;

Tema1::Tema1()
{

}

Tema1::~Tema1()
{

}

void Tema1::Init()
{
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	
	current_number_of_lifes = NUMBER_OF_LIFES;
	// initialize tx and ty (the translation steps)

	scaleX = 0.7f;
	scaleY = 0.9f;
	
	scale_X_power_bar = 0.01f;

	float y_coord = 0;
	float x_coord = 0;
	string balloon_name = "";
	string polyline_name = "";
	string shuriken_name = "";
	string life_circle_name = "";

	for (int i = 0; i < NUMBER_OF_LIFES; i++) {
		array_of_lifes[i].color = glm::vec3(1, 0, 1);
		glm::vec3 life_circle_corner = glm::vec3(x_initial_life_coord - i * space_between, y_life_coord, 0);
		life_circle_name = "life_circle" + to_string(i);

		array_of_lifes[i].object = Objects_2D::CreateCircle(life_circle_name, glm::vec3(0, 0, 0), LIFE_CIRCLE_RADIUS, glm::vec3(1, 0, 1), true);
		array_of_lifes[i].center = life_circle_corner;
		array_of_lifes[i].current_x = array_of_lifes[i].center.x;
		array_of_lifes[i].current_y = array_of_lifes[i].center.y;
		AddMeshToList(array_of_lifes[i].object);
	}

	for (int i = 0; i < 2 * NUMBER_OF_BALLOONS; i += 2) {
		
		//generating the centers of the balloons
		int y_range = 500 - 0 + 1;
		float y_coord = -600 + rand() % y_range;
		x_coord = x_coord_offset + 75 * i;

		glm::vec3 ballon_corner = glm::vec3(x_coord, y_coord, 0);
		glm::vec3 polyline_corner = ballon_corner + glm::vec3(0, -scaleY * RADIUS, 0);
		
		balloon_name = "balloon" + to_string(i / 2);
		polyline_name = "polyline" + to_string(i / 2);
		
		//creating ballons
		if(i % 4 == 0)
			array_of_balloons[i].color = glm::vec3(1, 0, 0); // red balloon
		else
			array_of_balloons[i].color = glm::vec3(1, 1, 0); // yellow balloon
		array_of_balloons[i].object = Objects_2D::CreateCircle(balloon_name, glm::vec3(0, 0, 0), RADIUS, array_of_balloons[i].color, true);
		array_of_balloons[i].center = ballon_corner;
	
		array_of_balloons[i].current_y = y_coord;
		array_of_balloons[i].current_x = x_coord;
		AddMeshToList(array_of_balloons[i].object);

		//creating polylines
		if (i % 4 == 0)
			array_of_balloons[i + 1].color = glm::vec3(1, 0, 0); // red balloon
		else
			array_of_balloons[i + 1].color = glm::vec3(1, 1, 0); // yellow balloon
		array_of_balloons[i + 1].object = Objects_2D::CreatePolyline(polyline_name, glm::vec3(0, 0, 0) + glm::vec3(0, -scaleY * RADIUS, 0),
																	 WIDTH_FACTOR, HEIGHT_FACTOR, array_of_balloons[i + 1].color, true);
		array_of_balloons[i + 1].center = polyline_corner;
		
		array_of_balloons[i + 1].current_y = polyline_corner.y;
		array_of_balloons[i + 1].current_x = polyline_corner.x;
		AddMeshToList(array_of_balloons[i + 1].object);

		array_of_modelMatrix_ballons[i/2] = glm::mat3(1) * Transform2D::Scale(sin(scaleX), sin(scaleY));
	}

	for (int i = 0; i < NUMBER_OF_SHURIKENS; i++) {
		//generating the centers of the shurikens
		int x_range = 200 - 0 + 1;
		float x_coord = resolution.x + rand() % x_range;
		y_coord = y_coord_offset + 175 * i;

		glm::vec3 shuriken_corner = glm::vec3(x_coord, y_coord, 0);

		shuriken_name = "shuriken" + to_string(i);
		

		//creating shurikens
		array_of_shurikens[i].object = Objects_2D::CreateShuriken(shuriken_name, glm::vec3(0, 0, 0), SHURIKEN_SIDE, glm::vec3(0, 1, 1), true);
		array_of_shurikens[i].center = shuriken_corner;
		array_of_shurikens[i].color = glm::vec3(0, 1, 1); // cyan shurikens
		array_of_shurikens[i].current_x = x_coord;
		array_of_shurikens[i].current_y = y_coord;
		AddMeshToList(array_of_shurikens[i].object);
	}

	translateY_bow_arrow = resolution.y / 2;

	bow_corner = glm::vec3(100, resolution.y / 2, 0);
	arrow_corner = glm::vec3(100.0f + RECTANGLE_WIDTH + TRIANGLE_SIDE * 1.73 / 2, resolution.y / 2, 0);
	power_bar_corner = glm::vec3(50, 50, 0);

	arrow.color = glm::vec3(0, 0.5, 0);
	arrow.object = Objects_2D::CreateArrow("arrow1", glm::vec3(0, 0, 0), RECTANGLE_HEIGHT, RECTANGLE_WIDTH, TRIANGLE_SIDE, arrow.color, true);
	arrow.center = arrow_corner;
	AddMeshToList(arrow.object);

	bow.color = glm::vec3(0, 1, 0);
	bow.object = Objects_2D::CreateBow("bow1", glm::vec3(0, 0, 0), BOW_RADIUS, bow.color, true);
	bow.center = bow_corner;
	bow.current_x = bow.center.x;
	AddMeshToList(bow.object);

	power_bar.color = glm::vec3(1, 1, 1);
	power_bar.object = Objects_2D::CreateRectangle("power_bar", glm::vec3(0, 0, 0), POWER_BAR_HEIGHT, POWER_BAR_MAX_WIDTH, power_bar.color, true);
	power_bar.center = power_bar_corner;
	AddMeshToList(power_bar.object);
/*
	Shape balloon;
	balloon.object = Objects_2D::CreateCircle("balloon", glm::vec3(0, 0, 0), RADIUS, glm::vec3(1, 0, 0), true);
	AddMeshToList(balloon.object);
	*/
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	if (gameOver == false) {
		string balloon_name = "";
		string polyline_name = "";
		string shuriken_name = "";
		string life_circle_name = "";

		/*{
			modelMatrix = glm::mat3(1);
			RenderMesh2D(meshes["balloon"], shaders["VertexColor"], modelMatrix);

		}*/
		{
			modelMatrix_bow = glm::mat3(1);
			modelMatrix_arrow = glm::mat3(1);

			if (arrow.current_x > resolution.x || arrow.current_x < 0 ||
				arrow.current_y > resolution.y || arrow.current_y < 0) {
				arrowRelease = false;
				arrow_onRelease_step = 0;
			}

			if (arrowRelease == false) {
				//cout << "bla" << endl;
				arrow.current_x = bow.center.x + cos(angle_in_radians) * (RECTANGLE_WIDTH + TRIANGLE_SIDE * 1.73 / 2);
				arrow.current_y = bow.center.y + sin(angle_in_radians) * (RECTANGLE_WIDTH + TRIANGLE_SIDE * 1.73 / 2);


				modelMatrix_arrow *= Transform2D::Translate(bow.center.x, translateY_bow_arrow);
				modelMatrix_arrow *= Transform2D::Rotate(angle_in_radians);
				modelMatrix_arrow *= Transform2D::Translate(TRIANGLE_SIDE * 1.73 / 2 + RECTANGLE_WIDTH, 0);
			}
			else {
				//cout << "Am ramas aici" << endl;
				arrow_onRelease_step += (arrow_speed * deltaTimeSeconds * 100);
				arrow.current_x = bow.center.x + cos(angle_on_release) * arrow_onRelease_step;
				arrow.current_y = translateY_bow_arrow + sin(angle_on_release) * arrow_onRelease_step;

				modelMatrix_arrow *= Transform2D::Translate(arrow.current_x, arrow.current_y);
				modelMatrix_arrow *= Transform2D::Rotate(angle_on_release);
				modelMatrix_arrow *= Transform2D::Translate(TRIANGLE_SIDE * 1.73 / 2 + RECTANGLE_WIDTH, 0);

				for (int i = 0; i < 2 * NUMBER_OF_BALLOONS; i += 2) {

					float distance = sqrtf((arrow.current_x - array_of_balloons[i].current_x) *
						(arrow.current_x - array_of_balloons[i].current_x) +
						(arrow.current_y - array_of_balloons[i].current_y) *
						(arrow.current_y - array_of_balloons[i].current_y));
					if (distance < 1.5 * RADIUS) { // collision

						if (array_of_balloons[i].color == glm::vec3(1, 1, 0))  // is yellow
							totalScore += yballoon_score;
						else
							totalScore += rballoon_score;
						cout << "current_score: " << totalScore << endl;

						array_of_modelMatrix_ballons[i / 2] = glm::mat3(1) * Transform2D::Scale(scaleX, scaleY);
						for (int j = 0; j < NUMBER_OF_BALLOONS; j++) {
							jump_scale_onDestruction_X[j] = 100 * scaleX;
							jump_scale_onDestruction_Y[j] = 100 * scaleY;
						}
						while (jump_scale_onDestruction_X[i / 2] > 0 && jump_scale_onDestruction_Y[i / 2] > 0) {
							//cout << jump_scale_onDestruction_X[i / 2] << " " << jump_scale_onDestruction_Y[i / 2] << endl;
							jump_scale_onDestruction_X[i / 2] -= deltaTimeSeconds;
							jump_scale_onDestruction_Y[i / 2] -= deltaTimeSeconds;
							array_of_modelMatrix_ballons[i / 2] = glm::mat3(1) * Transform2D::Scale(jump_scale_onDestruction_X[i / 2], jump_scale_onDestruction_Y[i / 2]);
							array_of_modelMatrix_ballons[i / 2] *= Transform2D::Translate(array_of_balloons[i].current_x, array_of_balloons[i].current_y);
						}
						array_of_modelMatrix_ballons[i / 2] *= Transform2D::Translate(array_of_balloons[i].center.x, array_of_balloons[i].center.y);

						array_of_balloons[i].current_x = array_of_balloons[i].center.x;
						array_of_balloons[i].current_y = array_of_balloons[i].center.y;
						balloon_translate_y[i / 2] = 0;
					}
				}
			}
			//s	cout << arrow.current_x << " " << arrow.current_y << " " << arrow_speed << " " << angle_on_release << endl;
			//	modelMatrix_arrow *= Transform2D::Translate(TRIANGLE_SIDE * 1.73 / 2 + RECTANGLE_WIDTH, translateY_bow_arrow);

				//cout << bow.current_x << " " << translateY_bow_arrow << " " << arrow.current_x << " " << arrow.current_y << endl;
			modelMatrix_bow *= Transform2D::Translate(bow.center.x, translateY_bow_arrow);
			modelMatrix_bow *= Transform2D::Rotate(angle_in_radians);
			bow.current_y = translateY_bow_arrow;

			RenderMesh2D(meshes["arrow1"], shaders["VertexColor"], modelMatrix_arrow);
			RenderMesh2D(meshes["bow1"], shaders["VertexColor"], modelMatrix_bow);
		}

		{
			for (int i = 0; i < current_number_of_lifes; i++) {
				array_of_modelMatrix_life_circles[i] = glm::mat3(1);
				array_of_modelMatrix_life_circles[i] *= Transform2D::Translate(array_of_lifes[i].current_x, array_of_lifes[i].current_y);
				life_circle_name = "life_circle" + to_string(i);

				RenderMesh2D(meshes[life_circle_name], shaders["VertexColor"], array_of_modelMatrix_life_circles[i]);
			}
		}

		{
			if (mousePress == true) {
				if (1 - scale_X_power_bar > 0.01) {
					scale_X_power_bar += 0.01;
					modelMatrix_power_bar = glm::mat3(1);
					modelMatrix_power_bar *= Transform2D::Translate(50, 50);
					modelMatrix_power_bar *= Transform2D::Scale(scale_X_power_bar, 1);
				}

				RenderMesh2D(meshes["power_bar"], shaders["VertexColor"], modelMatrix_power_bar);
			}

			if (mouseRelease == true) {
				arrow_speed = 10 * scale_X_power_bar;
				scale_X_power_bar = 0.01;
				mouseRelease = false;
			}
		}

		{
			for (int i = 0; i < 2 * NUMBER_OF_BALLOONS; i += 2) {

				array_of_modelMatrix_ballons[i / 2] = glm::mat3(1);
				balloon_translate_y[i / 2] += deltaTimeSeconds;
				array_of_modelMatrix_ballons[i / 2] *= Transform2D::Scale(scaleX, scaleY);
				array_of_modelMatrix_ballons[i / 2] *= Transform2D::Translate(array_of_balloons[i].center.x, array_of_balloons[i].current_y);
				array_of_balloons[i].current_y += balloon_translate_y[i / 2];

				//cout << array_of_balloons[i].current_y << " " << balloon_translate_y[i / 2] << endl;
				if (array_of_balloons[i].current_y - 3 * RADIUS >= resolution.y) {
					array_of_modelMatrix_ballons[i / 2] = glm::mat3(1) * Transform2D::Scale(sin(scaleX), sin(scaleY));
					array_of_modelMatrix_ballons[i / 2] *= Transform2D::Translate(array_of_balloons[i].center.x, array_of_balloons[i].center.y);

					array_of_balloons[i].current_y = array_of_balloons[i].center.y;
					balloon_translate_y[i / 2] = 0;
				}

				//cout << i << endl;

				balloon_name = "balloon" + to_string(i / 2);
				polyline_name = "polyline" + to_string(i / 2);
				//cout << balloon_name << " " << polyline_name << endl;
				RenderMesh2D(meshes[balloon_name], shaders["VertexColor"], array_of_modelMatrix_ballons[i / 2]);
				RenderMesh2D(meshes[polyline_name], shaders["VertexColor"], array_of_modelMatrix_ballons[i / 2]);

			}
		}

		{
			for (int i = 0; i < NUMBER_OF_SHURIKENS; i++) {

				shuriken_translate_x[i] += deltaTimeSeconds;
				shuriken_angularStep[i] += deltaTimeSeconds;
				array_of_modelMatrix_shurikens[i] = glm::mat3(1);
				array_of_modelMatrix_shurikens[i] *= Transform2D::Translate(array_of_shurikens[i].current_x, array_of_shurikens[i].center.y);
				array_of_modelMatrix_shurikens[i] *= Transform2D::Rotate(shuriken_angularStep[i]);
				//			array_of_modelMatrix_shurikens[i] *= Transform2D::Translate(-shuriken_translate_x[i], 0);
							//array_of_modelMatrix_shurikens[i] *= Transform2D::Translate(-array_of_shurikens[i].current_x, -array_of_shurikens[i].current_y);
				array_of_shurikens[i].current_x -= shuriken_translate_x[i];

				//cout << array_of_shurikens[i].current_x << " " << shuriken_translate_x[i] << " " << shuriken_angularStep[i] << endl;
				if (array_of_shurikens[i].current_x < 0) {
					//cout << "Uite" << endl;
					array_of_modelMatrix_shurikens[i] = Transform2D::Translate(array_of_shurikens[i].center.x, array_of_shurikens[i].center.y);

					array_of_shurikens[i].current_x = array_of_shurikens[i].center.x;
					shuriken_translate_x[i] = 0;
				}

				//cout << array_of_shurikens[i].current_x << " " << array_of_shurikens[i].current_y << "    " << bow.current_x << " " << bow.current_y << endl;
				float dx = array_of_shurikens[i].current_x - bow.current_x;
				float dy = array_of_shurikens[i].current_y - bow.current_y;
				float distance = sqrtf(dx * dx + dy * dy);

				if (distance < BOW_RADIUS + SHURIKEN_SIDE) {
					current_number_of_lifes--;

					if (current_number_of_lifes == 0)
						gameOver = true;

					array_of_modelMatrix_shurikens[i] = glm::mat3(1) * Transform2D::Translate(array_of_shurikens[i].center.x, array_of_shurikens[i].center.y);
					array_of_shurikens[i].current_x = array_of_shurikens[i].center.x;
					shuriken_translate_x[i] = 0;
				}

				shuriken_name = "shuriken" + to_string(i);
				RenderMesh2D(meshes[shuriken_name], shaders["VertexColor"], array_of_modelMatrix_shurikens[i]);
			}
		}
	}
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W)) {
		if (translateY_bow_arrow < resolution.y - BOW_RADIUS) {
			translateY_bow_arrow += deltaTime * 500;
		}
	}
	else if (window->KeyHold(GLFW_KEY_S)) {
		if (translateY_bow_arrow > BOW_RADIUS) {
			translateY_bow_arrow -= deltaTime * 500;
		}
	}
}

void Tema1::OnKeyPress(int key, int mods)
{

}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	int x1 = mouseX, x2 = arrow.center.x;
	int y1 = mouseY, y2 = translateY_bow_arrow;
	angle_in_radians = atanf((float)(x2 - x1) / (y2 - y1) - M_PI / 2);
	//cout << angle_in_radians << endl;
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	mousePress = true;
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	mousePress = false;
	mouseRelease = true;
	arrowRelease = true;
	angle_on_release = angle_in_radians;
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
