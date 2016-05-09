#pragma once
#include "PhysicsObject.h"

class RigidBody : public PhysicsObject
{
public:
	RigidBody(vec3 position, vec3 velocity, quat rotation, float mass);

	vec2 position;
	vec2 velocity;

	float mass;
	float rotation2D;

	virtual void Update(vec2 gravity, float timeStep);
	virtual void Debug();
	void ApplyForce(vec2 force);
	void ApplyForceToActor(RigidBody* actor2, vec3 force);
};