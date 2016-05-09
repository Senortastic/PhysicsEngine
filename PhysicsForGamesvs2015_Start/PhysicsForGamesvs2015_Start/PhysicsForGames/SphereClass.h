#pragma once
#include "RigidBody.h"

class SphereClass : public RigidBody
{
public:
	float _radius;
	SphereClass(vec3 position, vec3 velocity, float mass, float radius, vec4 colour);
	virtual void MakeGizmo();
};