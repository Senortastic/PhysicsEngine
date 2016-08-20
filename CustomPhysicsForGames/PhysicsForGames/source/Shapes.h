#pragma once
#include "../Gizmos.h"
#include "../glm/glm.hpp"

using namespace glm;
class Shape
{
public:
	int GetShapeType() { return static_cast<int>(m_id); }
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
	Shape(ShapeType id) : m_id(id) {}
private:
	ShapeType m_id;
};

class AABB : public Shape
{
public:
	//TODO: overload for constructor and store colour
	AABB(vec3 size) : Shape(ShapeType::AABB), m_size(size) {}
	vec3 GetSize() const { return m_size; }
	void Draw(vec3 position) const override
	{
		Gizmos::addAABBFilled(position, m_size, vec4(0, 0.5, 0, 1));
	}
private:
	vec3 m_size;
};

class Plane : public Shape
{
public:
	Plane(vec3 normal, float offset) : Shape(ShapeType::Plane), m_normal(normal), m_offset(offset) {}
	vec3 GetNormal() const { return m_normal; }
	float GetDistance() const { return m_offset; }
	void Draw(vec3 position) const override
	{
		Gizmos::addAABBFilled(vec3(0, m_offset, 0), vec3(100.f, 0.01f, 100.f), vec4(0.25f, 0.25f, 0.25f, 1));
	}
private:
	vec3 m_normal;
	float m_offset; //distance
};

class Sphere : public Shape
{
public:
	Sphere(float radius) : Shape(ShapeType::Sphere), m_radius(radius){}
	float GetRadius() const { return m_radius; }
	void Draw(vec3 position) const override
	{
		Gizmos::addSphereFilled(position, m_radius, 10, 10, vec4(0.5f, 0, 0, 1));
	}
private:
	float m_radius;
};