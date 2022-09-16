#pragma once
#define RENDERER
#include <vector>

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
