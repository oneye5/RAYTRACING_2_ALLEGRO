#include "Renderer.h"
#include "3dMethods.h"
#include<iostream>
#pragma region const vars
const float maxRayDist = 150;
const float rayStep = 0.5;
#pragma endregion
#pragma region viewportVars
Vector3 camPos;
Vector2 camRot;

int screenWidth;
int screenHeight;

Vector2 fov;

void ViewPort::InitViewPort(float CamPosX, float CamPosY, float CamPosZ,
	float CamRotX, float CamRotY,
	int ScreenWidth, int ScreenHeight,
	float XFov, float YFov)
{
	camPos = Vector3(CamPosX, CamPosY, CamPosZ);
	camRot = Vector2(CamRotX, CamRotY);
		screenWidth = ScreenWidth;
		screenHeight = ScreenHeight;

		fov = Vector2(XFov, YFov);
}

 vector<Shape> objects = vector<Shape>();
void ViewPort::InitGeometry()
{
	objects = vector<Shape>();
	objects.push_back(Shape(sphere, Vector3(0.0f, 1.0f, 10.0f),2.0f));
	//objects.push_back(Shape(sphere, Vector3(0.0f, 1.0f, 10.0f), 2.0f));
	//objects.push_back(Shape(sphere, Vector3(1.0f, 1.0f, 10.0f), 500.0f));
	objects.push_back(Shape(sphere, Vector3(1.0f, 1.0f, 15.0f), 1.0f));
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
 float checkSphere(Shape& shape,Ray& ray)
 {
	 float distTo = getDistanceTo(ray.pos, shape.sphereOrigin);
	 if (shape.radius >= distTo)
	 {
		// std::cout << "\n hit data = " << distTo << " xyzs " << shape.sphereOrigin.x << " " << shape.sphereOrigin.y << " " << shape.sphereOrigin.z << " "
		//	 << ray.pos.x << " " << ray.pos.y << " " << ray.pos.z << " radius " << shape.radius;
		 ray.Hit = true;
	 }
	 return distTo;
 }
 void checkPoly()
 {

 }
 void checkAllIntersect(Ray& ray)
 {
	 float lowestDist = maxRayDist;
	 for (int i = 0; i < objects.size(); i++)
	 {
		 Shape& object = objects[i];
		 if (object.shapetype == sphere)
		 {
			float distance = checkSphere(object, ray); // returns dist
			if (ray.Hit == true)
				return;


			if (distance < lowestDist)
			{
				lowestDist = distance;
			}
		 }
		 else // poly check
		 {

		 }
	 }
	 ray.dist += (lowestDist );
 }
 Ray CastRay(Vector3 origin,Vector2 dir)
 {
	 Ray ray = Ray();
	 ray.Hit = false;
	 ray.dist = 0;
	 ray.pos = origin;
	 Vector3 posIncrement;
	 posIncrement = getRayPos(Vector3(0,0,0), 1.0f, dir); // get xyz change per 1 unit distance (used for efficiency)

	 for (int d = 0; d < maxRayDist; d += rayStep)
	 {
		 ray.pos = origin + (posIncrement * d);
		 checkAllIntersect(ray);
		 d = ray.dist;
		 if (ray.Hit == true)
		 {
			 ray.col = Color(255, 255, 255);
			 return ray;
		 }
		 else
		 {
			 ray.col = Color(0, 0, 0);
		 }
	 }
	 return ray;
 }
 vector<Ray> CastRays() //y = yaw, x = pitch
 {
	 float startYaw = (camRot.y) - (fov.x / 2);
	 float endYaw = (camRot.y) + (fov.x / 2);
	 float currentYaw = startYaw;

	 float startPitch = (camRot.x) + (fov.y / 2);
	 float endPitch = (camRot.x) - (fov.y / 2);
	 float currentPitch = startPitch;

	 vector<Ray> rays;

	 for (int pixelY = 0; pixelY < screenHeight ; pixelY++)
	 {
		 currentPitch = startPitch + (pixelY * (screenHeight / fov.y));
		 for (int pixelX = 0; pixelX < screenWidth ;pixelX++ )
		 {
			 currentYaw = startPitch + (pixelX * (screenWidth / fov.x));
			 rays.push_back(CastRay(camPos,Vector2(currentYaw,currentPitch))); 
			 
		 }
		std::cout << "size \n" << rays.size();
	 }

	 return rays;
 }
 vector<PIXEL> ViewPort::Render()
 {
	auto rays =	 CastRays();
	//convert to PIXEL class
	vector<PIXEL> pixels;
	for (int i = 0; i < rays.size(); i++)
	{
		auto ray = rays[i];
		pixels.push_back(PIXEL(ray.col.R, ray.col.G, ray.col.B));
	}
	return pixels;
 }
#pragma endregion