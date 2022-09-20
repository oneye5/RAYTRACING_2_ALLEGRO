#include "Renderer.h"
#include "3dMethods.h"
#include<iostream>
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

void ViewPort::InitViewPort(float CamPosX, float CamPosY, float CamPosZ,
	float CamRotX, float CamRotY,
	int ScreenWidth, int ScreenHeight,
	float XFov, float YFov,
	float RayStep)
{
	camPos = Vector3(CamPosX, CamPosY, CamPosZ);
	camRot = Vector2(CamRotX, CamRotY);
		screenWidth = ScreenWidth;
		screenHeight = ScreenHeight;

		fov = Vector2(XFov, YFov);
		rayStep = RayStep;
}

 vector<Shape> objects = vector<Shape>();
void ViewPort::InitGeometry()
{
	Shape s1 = Shape(sphere, Vector3(0, 10, 1), 5.0f);
	objects.push_back(s1);
}
#pragma endregion

#pragma region renderer
 class Ray
 {
 public:
	 Ray()
	 {

	 }
	 bool Hit;
	 Vector3 pos;
	 Vector2 dir;
	 float dist;
	 Color col;
 };
 void checkSphere(Shape& shape,Ray& ray)
 {
	 auto rayObjDist = getDistanceTo(ray.pos, shape.sphereOrigin);
	 if (rayObjDist < shape.radius)
	 {
		 //additional precision could be calculated here ( setting a new distance at the exact intersection)
		 ray.Hit = true;
		 ray.col = Color(255, 255, 255);
	 }
 }
 void checkPoly()
 {

 }
 void checkAllIntersect(Ray& ray)
 {
	 for (int i = 0; i < objects.size(); i++)
	 {
		 if (objects[i].shapetype == sphere)
		 {
			  checkSphere(objects[i],ray);
		 }
	 }
 }
 Ray CastRay(Vector3 origin,Vector2 dir)
 {
	 Ray ray = Ray();
	 ray.col = Color(0,0,0);
	 ray.Hit = false;

	 for (float dist = 0; dist < maxRayDist; dist += rayStep)
	 {
		 ray.dist = dist;
		 ray.pos = getRayPos(origin, dist, dir);
		 checkAllIntersect(ray);

		 if (ray.Hit)
		 {
			 return ray;
		 }
	 }
	 return ray;
 }
 vector<Ray> CastRays()
 {
	 std::cout << "castingRays\n";
	 float startAngleY = camRot.y - (fov.x / 2.0f);
	 float endAngleY = camRot.y + (fov.x / 2.0f);

	 float startAngleX = camRot.x - (fov.y / 2.0f);
	 float endAngleX = camRot.x + (fov.y / 2.0f);

	 float angleStepX = (fov.y / screenWidth);
	 float angleStepY = (fov.x / screenHeight);

	 vector<Ray> Rays;
	 for (float xAngle = startAngleX; xAngle < endAngleX; xAngle += angleStepX) // y pixel iteration
	 {
		 for (float yAngle = startAngleX; yAngle < endAngleX; yAngle += angleStepY) // xpixel iteration
		 {
			 Rays.push_back( CastRay(camPos, Vector2(xAngle, yAngle)));
		 }
	 }
	
	 return Rays;
 }
 vector<PIXEL> ViewPort::Render()
 {
	 auto rays = CastRays();
	 vector<PIXEL> pixels;
	 std::cout << "pixel count " << rays.size();
	 for (int i = 0; i < rays.size(); i++)
	 {
		 Color col = Color(rays[i].col);
		 pixels.push_back(PIXEL(col.R,col.G,col.B));
	 }
	 return pixels;
 }
#pragma endregion