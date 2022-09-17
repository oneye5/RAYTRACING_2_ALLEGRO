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
enum shapeType
{
	sphere,
	polygon
};
class Vertex
{
	Vector3 Pos;
};
class Triangle
{
	vector<Vertex> vertices;
};
 class Shape
{
	public:
	//poly
	shapeType shapetype;
	vector<Triangle> triangles;
	Shape(shapeType& ShapeType, vector<Triangle>& Triangles)
	{
		ShapeType = ShapeType;
		triangles = Triangles;
	}
	Shape(shapeType ShapeType, vector<Triangle> Triangles)
	{
		ShapeType = ShapeType;
		triangles = Triangles;
	}

	//sphere
	Vector3 sphereOrogin;
	float radius;
	Shape(shapeType ShapeType, Vector3 SphereOrogin, float Radius)
	{
		ShapeType = ShapeType;
		sphereOrogin = SphereOrogin;
		radius = Radius;
	}
};
#pragma endregion
#pragma region enviroment
 vector<Shape> shapes = vector<Shape>();
 void initMap()
 {
	 auto shape = Shape(sphere, Vector3(0, 0, 0), 10);
	
 }
#pragma endregion 
#pragma region renderer
 class RayHit
 {
	 Vector3 pos;
	 Vector2 dir;
	 float dist;
	 Color col;
 };
 void checkSphere()
 {

 }
 RayHit CastRay(Vector3 orogin,Vector2 dir)
 {
	
 }

#pragma endregion