#pragma once
#define RENDERER
#include <vector>
using std::vector;
class PIXEL
{
	public:
	unsigned char R;
	unsigned char G;
	unsigned char B;
	PIXEL(unsigned char r, unsigned char g, unsigned char b)
	{
		R = r;
		G = g;
		B = b;
	}
};
class ViewPort
{
public:
	//public methods
	void InitViewPort(float CamPosX, float CamPosY, float CamPosZ,
		float CamRotX, float CamRotY,
		int ScreenWidth, int ScreenHeight,
		float XFov, float YFov,
		float RayStep);
	void InitGeometry();
	vector<PIXEL> Render();
};
