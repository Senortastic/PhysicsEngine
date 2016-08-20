#pragma once
#include <memory>
#include "RigidBody.h"
#include "Shapes.h"

class PhysicsObject
{
public:
	PhysicsObject(vec3 position, Shape* shape = nullptr, RigidBody* rigidbody = nullptr) : position(position), rigidBody(rigidbody) {}

	virtual void Update(vec3 gravity, float deltaTime) { if (HasRigidBody()) position += rigidBody->GetPositionDelta(); }
	virtual void Draw();
	void AddPosition();
	void AddForce();
	void AddVelocity();
	void AddMomentum();
	float GetMass();
	Shape* GetShape();
	vec3 GetVelocity();
	vec3 GetMomentum();
	vec3 GetPosition();
	bool HasRigidBody() { return rigidBody != nullptr; }
	vec3 position;
	std::unique_ptr<Shape> shape;
	std::unique_ptr<RigidBody> rigidBody;
};
