#pragma once
#include "glm\glm.hpp"

enum ShapeType
{
	PLANE = 0,
	SPHERE = 1,
	BOX = 2,
};

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::quat;

class PhysicsObject
{
public:
	ShapeType _shapeID;
	virtual void Update(vec3 gravity, float timeStep) = 0;
	virtual void Debug() = 0;
	virtual void MakeGizmos() = 0;
	virtual void ResetPosition() {};
};