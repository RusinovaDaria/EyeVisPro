#pragma once
#include <vector>
#include <memory>

using namespace System::Drawing;

public class Point3D
{
public: 
	float x;
	float y;
	float z;

	Point3D() = default;
	Point3D(const Point3D& p) = default;
	Point3D(Point3D&& p) = default;

	Point3D(float px, float py, float pz) : x(px), y(py), z(pz) {};
};

public class Vector3D
{
public: 
	float x; 
	float y;
	float z;

	Vector3D() = default;
	Vector3D(const Vector3D &v) = default;
	Vector3D(Vector3D &&v) = default;

	Vector3D(float px, float py, float pz) : x(px), y(py), z(pz) {};
	Vector3D(Point3D& p1, Point3D& p2)
	{
		x = p2.x - p1.x;
		y = p2.y - p1.y;
		z = p2.z - p1.z;
	};
};

public class Ray3D
{
public:
	Point3D start;
	Vector3D direction; 

	Ray3D() = default;
	Ray3D(const Ray3D & r) = default;
	Ray3D(Ray3D && r) = default;

	Ray3D(Point3D& s, Vector3D& d) : start(s), direction(d) {};
	Ray3D(Point3D& s, Point3D& p) : start(s), direction(s, p) {};
};

public class ColorRGBA
{
public:
	int r;
	int g;
	int b;
	float a;

	ColorRGBA() = default;
	ColorRGBA(const ColorRGBA &c) = default;
	ColorRGBA(ColorRGBA && c) = default;

	ColorRGBA(int pr, int pg, int pb, float pa = 1) :
		r(pr), g(pg), b(pb), a(pa) {};
	ColorRGBA(Color ^c)
	{
		r = c->R;
		g = c->G;
		b = c->B;
		a = c->A;
	}
};

public class Sphere
{
public:
	float radius;
	Point3D center;
	ColorRGBA color; 
};

