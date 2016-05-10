#include "RigidBody.h"

RigidBody::RigidBody(vec3 position, vec3 velocity, quat rotation, float mass)
{
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_mass = mass;
}

void RigidBody::ApplyForce(vec2 force)
{

}

void RigidBody::ApplyForceToActor(RigidBody* actor2, vec3 force)
{

}

void RigidBody::Update(vec2 gravity, float timeStep)
{

}