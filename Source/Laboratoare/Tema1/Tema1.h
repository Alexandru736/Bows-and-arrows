
#include <Component/SimpleScene.h>
#include <Core/Engine.h>

#define BALLOON_MOVING_RATIO 5.0f
#define SHURIKEN_MOVING_RATIO 5.0f
#define SHURIKEN_SIDE 30.0f
#define TRIANGLE_SIDE 25.0f //arrow's triangle
#define RECTANGLE_HEIGHT 8.0f //arrow's rectangle height
#define RECTANGLE_WIDTH 85.0f //arrow's rectangle width
#define RADIUS 50.0f // ballon's radius
#define WIDTH_FACTOR 15.0f // polyline's maximum width
#define HEIGHT_FACTOR 10.0f
#define BOW_RADIUS 40.0f // bow's radiusfref
#define NUMBER_OF_BALLOONS 12
#define NUMBER_OF_SHURIKENS 4
#define POWER_BAR_HEIGHT 50.0f
#define POWER_BAR_MAX_WIDTH 100.0f
#define NUMBER_OF_LIFES 3
#define LIFE_CIRCLE_RADIUS 10.0f


class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

	struct Shape{
		Mesh* object;
		glm::vec3 center;
		glm::vec3 color;
		float current_x;
		float current_y;
	};

private:

	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:

	int totalScore = 0;
	int rballoon_score = -50;
	int yballoon_score = 30;

	float scaleX, scaleY;
	float angularStep;
	float x_coord_offset = 450; //offset to create the first balloon
	float y_coord_offset = 50; //offset to create the first shuriken
	bool gameOver = false;
	bool mousePress = false;
	bool mouseRelease = false;
	bool arrowRelease = false;

	glm::ivec2 resolution = window->GetResolution();

	GLenum cullFace;
	GLenum polygonMode;

	Shape array_of_balloons[2 * NUMBER_OF_BALLOONS];
	float balloon_translate_y[NUMBER_OF_BALLOONS]; //coordonates of each balloon's y_coord corner
	glm::mat3 array_of_modelMatrix_ballons[NUMBER_OF_BALLOONS];
	float jump_scale_onDestruction_X[NUMBER_OF_BALLOONS];
	float jump_scale_onDestruction_Y[NUMBER_OF_BALLOONS];

	Shape array_of_shurikens[NUMBER_OF_SHURIKENS];
	float shuriken_translate_x[NUMBER_OF_SHURIKENS];
	float shuriken_angularStep[NUMBER_OF_SHURIKENS];
	glm::mat3 array_of_modelMatrix_shurikens[NUMBER_OF_SHURIKENS];
	
	float translateY_bow_arrow;

	Shape arrow;
	glm::vec3 arrow_corner;
	glm::mat3 modelMatrix_arrow;	
	float angle_in_radians;
	float angle_on_release;
	float arrow_speed;
	float arrow_onRelease_step;
	

	Shape bow;
	glm::vec3 bow_corner;
	glm::mat3 modelMatrix_bow;

	Shape power_bar;
	glm::vec3 power_bar_corner;
	glm::mat3 modelMatrix_power_bar;
	float scale_X_power_bar;

	Shape array_of_lifes[NUMBER_OF_LIFES];
	glm::mat3 array_of_modelMatrix_life_circles[NUMBER_OF_LIFES];
	const float space_between = 30.0f;
	const float y_life_coord = resolution.y - 3 / 2 * LIFE_CIRCLE_RADIUS;
	const float x_initial_life_coord = resolution.x - 3 / 2 * LIFE_CIRCLE_RADIUS;
	int current_number_of_lifes;

	glm::mat3 modelMatrix;
};