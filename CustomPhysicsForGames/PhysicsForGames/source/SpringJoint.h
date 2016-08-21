#pragma once
#include "PhysicsObject.h"

class SpringJoint : public PhysicsObject
{
public:
	SpringJoint(std::shared_ptr<PhysicsObject> connection1, std::shared_ptr<PhysicsObject> connection2, float springCoefficient, float damping, float restingDistance = 0);

private:
	void virtual Update(vec3 gravity, float timestep);
	void virtual Draw();
	std::shared_ptr<PhysicsObject> connections[2];
	float damping;
	float restLength;
	float springCoefficient;
};