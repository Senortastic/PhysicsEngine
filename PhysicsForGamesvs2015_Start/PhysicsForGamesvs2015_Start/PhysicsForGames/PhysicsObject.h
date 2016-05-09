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
	void virtual Update(vec3 gravity, float timeStep) = 0;
	void virtual Debug() = 0;
	void virtual MakeGizmos() = 0;
	void virtual ResetPosition() {};
};