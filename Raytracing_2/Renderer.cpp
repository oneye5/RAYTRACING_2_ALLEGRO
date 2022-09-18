#include "Renderer.h"
#pragma region const vars
const float maxRayDist = 100;
#pragma endregion
#pragma region viewportVars
Vector3 camPos;
Vector2 camRot;

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
 class Ray
 {
 public:
	 bool Hit;
	 Vector3 pos;
	 Vector2 dir;
	 float dist;
	 Color col;
 };
 float checkSphere()
 {

 }
 float checkPoly()
 {

 }
 void checkAllIntersect(Ray& ray)
 {

 }
 Ray CastRay(Vector3 orogin,Vector2 dir)
 {
	 auto ray= Ray();
	 
	 for (float dist = 0; dist < maxRayDist; dist += rayStep)
	 {
		 ray.dist = dist;
		 ray.pos = getRayPos(orogin, dist, dir);
		 checkAllIntersect(ray);

		 if (ray.Hit)
		 {
			 return ray;
		 }
	 }
 }
 void CastRays()
 {
	 float startAngleY = camRot.y - (fov.x / 2.0f);
	 float endAngleY = camRot.y + (fov.x / 2.0f);

	 float startAngleX = camRot.x + (fov.y / 2.0f);
	 float endAngleX = camRot.x - (fov.y / 2.0f);

	 float angleStepX = (fov.y / screenWidth);
	 float angleStepY = (fov.x / screenHeight);

	 vector<Ray> Rays;
	 for (float xAngle = startAngleX; xAngle < endAngleX; xAngle += angleStepX) // y pixel iteration
	 {
		 for (float yAngle = startAngleX; yAngle < endAngleX; yAngle += angleStepY) // xpixel iteration
		 {

		 }
	 }
	
 }

#pragma endregion