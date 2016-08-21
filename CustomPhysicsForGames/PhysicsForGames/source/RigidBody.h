#pragma once
#include "../glm/glm.hpp"

using namespace glm;

class RigidBody
{
public:
	RigidBody(float mass, vec3 initialVelocity) : mass(mass), velocity(initialVelocity){}
	vec3 Update(float deltaTime, vec3 gravity);
	float GetMass() { return mass; }
	vec3 GetVelocity() { return velocity; }
	vec3 GetMomentum() { return GetMass() * GetVelocity(); }
	void Stop() { velocity = vec3(0); }
	void AddVelocity(vec3 velocity) { this->velocity += velocity; }
	void AddMomentum(vec3 momentum) { AddVelocity( momentum / mass); }
	void AddForce(vec3 force) { this->force += force; }
private:
	float mass;
	vec3 velocity;
	vec3 force;
};
