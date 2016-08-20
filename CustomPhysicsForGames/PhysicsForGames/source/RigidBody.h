#pragma once
#include "../glm/glm.hpp"

using namespace glm;

class RigidBody
{
public:
	RigidBody(float mass, vec3 initialVelocity) : mass(mass), velocity(initialVelocity){}
	void Update(float deltaTime, vec3 gravity);
	float GetMass() { return mass; }
	vec3 GetVelocity() { return velocity; }
	vec3 GetMomentum() { return GetMass() * GetVelocity(); }
	vec3 GetPositionDelta() { return positionDelta; }
	void Stop() { velocity = vec3(0); }
	void AddVelocity(vec3 velocity) { velocity += velocity; }
	void AddMomentum(vec3 momentum) { AddVelocity(momentum / mass); }
	void AddForce(vec3 force) { force += force; }
private:
	float mass;
	vec3 velocity;
	vec3 force;
	vec3 positionDelta;
};
