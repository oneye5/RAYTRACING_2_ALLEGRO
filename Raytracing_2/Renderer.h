#pragma once
#define RENDERER
#include <vector>
#define PI 3.1415926535897
using std::vector;
//var definitions

class Vector3
{
public:
	float x;
	float y;
	float z;
	Vector3(float X = 0, float Y = 0, float Z = 0)
	{
		x = X;
		y = Y;
		z = Z;
	}
};
class Vector2
{
public:
	float x;
	float y;
	Vector2(float X = 0, float Y = 0)
	{
		x = X;
		y = Y;
	}
};
class Color
{
	unsigned char R;
	unsigned char G;
	unsigned char B;
};
float radToDeg(float rad)
{
	return(rad * (180 / PI));
}
float degToRad(float deg)
{
	return(deg * (PI / 180));
}
Vector3 getRayPos(Vector3 orogin, float dist, Vector2 A)
{
	Vector3 pos(
		orogin.x + ((sin(degToRad(A.y)) * cos(degToRad(A.x))) * dist),
		orogin.y + ((cos(degToRad(A.x))) * dist),
		orogin.z + ((cos(degToRad(A.y) * cos(degToRad(A.x)))) * dist)
	);
	return pos;
}
//declarations
class ViewPort
{
public:
	//methods
	void InitViewPort(float CamPosX, float CamPosY, float CamPosZ,
		float CamRotX, float CamRotY,
		int ScreenWidth, int ScreenHeight,
		float XFov, float YFov,
		float RayStep);
};
