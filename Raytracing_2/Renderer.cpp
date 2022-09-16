#include "Renderer.h"
#pragma region viewportVars
Vector3 camPos;
Vector2 rot;

int screenWidth;
int screenHeight;

Vector2 fov;

float rayStep;

void InitViewPort(float CamPosX, float CamPosY, float CamPosZ,
	float CamRotX, float CamRotY,
	int ScreenWidth, int ScreenHeight,
	float XFov, float YFov,
	float RayStep)
{

		screenWidth = ScreenWidth;
		screenHeight = ScreenHeight;

		rayStep = RayStep;
}
#pragma endregion
#pragma region Geometry
enum ShapeType
{
	Cube,
	Sphere,
	Polygon
};
class point
{
	float x;
	float y;
	float z;
};
class Shape
{
	vector<point> points;

	float oroginX;
	float oroginY;
	float oroginZ;

	//sphere
	float radius;
};
#pragma endregion
