#pragma once
#define PI 3.1415926535897
#include <vector>
using std::vector;

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
public:
	unsigned char R;
	unsigned char G;
	unsigned char B;
	Color(unsigned char r, unsigned char g, unsigned char b)
	{
		R = r;
		G = g;
		B = b;
	}
	Color()
	{

	}
};
float radToDeg(float rad)
{
	return(rad * (180 / PI));
}
float degToRad(float deg)
{
	return(deg * (PI / 180));
}
Vector3 getRayPos(Vector3 origin, float dist, Vector2 A)
{
	Vector3 pos(
		origin.x + ((sin(degToRad(A.y)) * cos(degToRad(A.x))) * dist),
		origin.y + ((cos(degToRad(A.x))) * dist),
		origin.z + ((cos(degToRad(A.y) * cos(degToRad(A.x)))) * dist)
	);
	return pos;
}
float getDistanceTo(Vector3 from, Vector3 to)
{
	float xDif = from.x - to.x;
	xDif = xDif * xDif;
	float yDif = from.y - to.y;
	yDif = yDif * yDif;
	float zDif = from.z - to.z;
	zDif = zDif * zDif;
	//squares all axis differences

	return sqrtf(xDif + yDif + zDif);
}
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
	Vector3 sphereOrigin;
	float radius;
	Shape(shapeType ShapeType, Vector3 SphereOrigin, float Radius)
	{
		ShapeType = ShapeType;
		sphereOrigin = SphereOrigin;
		radius = Radius;
	}
};
#pragma endregion