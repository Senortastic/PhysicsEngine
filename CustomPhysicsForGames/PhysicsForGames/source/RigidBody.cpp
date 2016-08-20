#include "RigidBody.h"

void RigidBody::Update(float deltaTime, vec3 gravity)
{
	vec3 acceleration = force / mass;
	vec3 oldVelocity = velocity;
	velocity += acceleration * deltaTime;
	velocity += gravity * deltaTime;

	positionDelta = (oldVelocity + velocity) * 0.5f * deltaTime;
	force = vec3(0);
}
