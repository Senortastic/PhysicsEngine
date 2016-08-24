#pragma once
#include "../Gizmos.h"
#include "../glm/glm.hpp"

using namespace glm;
class Shape
{
public:
	int GetShapeType() { return static_cast<int>(id); }
	static int GetShapeCount() { return static_cast<int>(ShapeType::Count); }
	virtual void Draw(vec3 position) const = 0;
protected:
	enum ShapeType
	{
		Plane,
		Sphere,
		AABB,
		Count,
	};
	Shape(ShapeType id) : id(id) {}
private:
	ShapeType id;
	vec3 colour;
};

class AABB : public Shape
{
public:
	AABB(vec3 size) : Shape(ShapeType::AABB), size(size) {}
	vec3 GetSize() const { return size; }
	void Draw(vec3 position) const override
	{
		Gizmos::addAABBFilled(position, size, vec4(0.5, 0.3, 0.5, 1));
	}
private:
	vec3 size;
};

class Plane : public Shape
{
public:
	Plane(vec3 normal, float offset) : Shape(ShapeType::Plane), normal(normal), offset(offset) {}
	vec3 GetNormal() const { return normal; }
	float GetDistance() const { return offset; }
	void Draw(vec3 position) const override
	{
		Gizmos::addAABBFilled(vec3(0, offset, 0), vec3(100.f, 0.01f, 100.f), vec4(0.7, 0.7, 0.7f, 1));
	}
private:
	vec3 normal;
	float offset;
};

class Sphere : public Shape
{
public:
	Sphere(float radius) : Shape(ShapeType::Sphere), radius(radius){}
	float GetRadius() const { return radius; }
	void Draw(vec3 position) const override
	{
		Gizmos::addSphereFilled(position, radius, 10, 10, vec4(0.1f, 0.1f, 0.1f, 1));
	}
private:
	float radius;
};