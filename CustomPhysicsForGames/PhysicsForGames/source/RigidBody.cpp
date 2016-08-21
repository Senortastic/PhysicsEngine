#include "RigidBody.h"

vec3 RigidBody::Update(float deltaTime, vec3 gravity)
{
	vec3 acceleration = force / mass;
	vec3 oldVelocity = velocity;
	velocity += acceleration * deltaTime;
	velocity += gravity * deltaTime;

	glm::vec3 positionDelta = (oldVelocity + velocity) * 0.5f * deltaTime;
	force = vec3(0);
	return positionDelta;
}
