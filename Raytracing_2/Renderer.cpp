#include "Renderer.h"
#include "3dMethods.h"
#include<iostream>
#pragma region const vars
const float maxRayDist = 75;
const float rayStep = 0.75;
#pragma endregion
#pragma region viewportVars

float temp_ShadeMulti = 0.2;

int screenWidth;
int screenHeight;

Vector3 camPos;
Vector2 camRot;

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
	objects.push_back(Shape(sphere, Vector3(0.0f, 0.0f, -10.0f),0.0f));


	objects.push_back(Shape(sphere, Vector3(0.0f, 3.0f, 10.0f), 5.0f));
	std::cout << "shape count = " << objects.size() << "\n";
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
	// std::cout << distTo << "\n";
	 if (shape.radius >= distTo)
	 {
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
	 ray.dir = dir;
	 ray.dist = 0;
	 ray.pos = origin;
	 Vector3 posIncrement;
	 
	 posIncrement = getRayPos(Vector3(0,0,0), 1.0f, dir); // get xyz change per 1 unit distance (used for efficiency)

	 for (int d = 0; d < maxRayDist; d += rayStep)
	 {
		// ray.pos = origin + (posIncrement * d);
		 ray.pos = getRayPos(origin, d, dir);
		 checkAllIntersect(ray);
		 d = ray.dist;
		 if (ray.Hit == true)
		 {
			 ray.col = Color(round( 255 /( ray.dist * temp_ShadeMulti)), round(255 / (ray.dist * temp_ShadeMulti)), round(255 / (ray.dist * temp_ShadeMulti)));
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
	 float yawS = fov.x / screenWidth;
	 float currentYaw = startYaw;

	 float startPitch = (camRot.x) + (fov.y / 2);
	 float pitchS = fov.y / screenHeight;
	 float currentPitch = startPitch;

	 // current A = (S*I) + start
	 //where S = fov/width


	 vector<Ray> rays;

	 for (int pixelY = 0; pixelY < screenHeight ; pixelY++)
	 {
		 currentPitch = (pitchS * pixelY) + startPitch;
		 for (int pixelX = 0; pixelX < screenWidth ;pixelX++ )
		 {
			 currentYaw = (yawS * pixelX) + startYaw;
			 rays.push_back(CastRay(camPos,Vector2(currentPitch,currentYaw))); 
			 
		 }
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
		/*
		std::cout<< "\n ray stats : ";
		std::cout<< ray.dir.x + 0;
		std::cout<< " ";
		std::cout<< ray.dir.y + 0;
		std::cout<< " ";
		std::cout<< ray.dist + 0;
		std::cout<< " ";
		std::cout<< ray.pos.x + 0;
		std::cout<< " ";
		std::cout<< ray.pos.y + 0;
		std::cout<< " ";
		std::cout<< ray.pos.z ;
		*/
		pixels.push_back(PIXEL(ray.col.R, ray.col.G, ray.col.B));
	}

	camRot.x += 0;
	camRot.y += 5;
	//camPos.z += 0.5;
	return pixels;
 }
#pragma endregion