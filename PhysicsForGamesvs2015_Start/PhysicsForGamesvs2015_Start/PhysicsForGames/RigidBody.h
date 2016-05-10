#pragma once
#include "PhysicsObject.h"

class RigidBody : public PhysicsObject
{
public:
	RigidBody(vec3 position, vec3 velocity, quat rotation, float mass);

	vec3 m_position;
	vec3 m_velocity;

	float m_force;
	float m_mass;
	vec2 m_rotation;

	virtual void Update(vec2 gravity, float timeStep);
	virtual void Debug();
	void ApplyForce(vec2 force);
	void ApplyForceToActor(RigidBody* actor2, vec3 force);
};