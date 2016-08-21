#include "SpringJoint.h"

SpringJoint::SpringJoint(std::shared_ptr<PhysicsObject> connection1, std::shared_ptr<PhysicsObject> connection2, float springCoefficient, float damping, float restingDistance): PhysicsObject(glm::vec3(0, 0, 0), nullptr, nullptr)
{
	connections[0] = connection1;
	connections[1] = connection2;

	this->springCoefficient = springCoefficient;
	this->damping = damping;
	if (restingDistance == 0)
		restLength = length(connections[0]->GetPosition() - connections[1]->GetPosition());
	else
		restLength = restingDistance;
}

void SpringJoint::Update(vec3 _gravity, float _timestep)
{
	vec3 offset = connections[0]->GetPosition() - connections[1]->GetPosition();
	vec3 direction = normalize(offset);
	float length = glm::length(offset);
	vec3 relativeVelocity = connections[0]->GetVelocity() - connections[1]->GetVelocity();
	vec3 force = -(springCoefficient * ((length - restLength) * direction)) - (damping * relativeVelocity);

	if (connections[0]->HasRigidBody())
	{
		connections[0]->AddForce(force);
	}

	if (connections[1]->HasRigidBody())
	{
		connections[1]->AddForce(-force);
	}
}

void SpringJoint::Draw()
{
	Gizmos::addLine(connections[0]->GetPosition(), connections[1]->GetPosition(), vec4(1, 1, 1, 1));
}