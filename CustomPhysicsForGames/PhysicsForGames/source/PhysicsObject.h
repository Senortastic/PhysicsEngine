#pragma once
#include <memory>
#include "RigidBody.h"
#include "Shapes.h"

class PhysicsObject
{
public:
	PhysicsObject(vec3 position, Shape* shape = nullptr, RigidBody* rigidbody = nullptr) : position(position), shape(shape), rigidBody(rigidbody) {}
	bool HasRigidBody() { return rigidBody != nullptr; }
	virtual void Update(vec3 gravity, float deltaTime) { if (HasRigidBody()) position += rigidBody->Update(deltaTime, gravity); }
	virtual void Draw() { if (shape) shape->Draw(position); }

	void AddPosition(vec3 positionDelta) { position += positionDelta; }
	void AddForce(vec3 force) { if (HasRigidBody()) rigidBody->AddForce(force); }
	void AddVelocity(vec3 velocity) { if (HasRigidBody()) rigidBody->AddVelocity(velocity); }
	void AddMomentum(vec3 momentum) { if(HasRigidBody()) rigidBody->AddMomentum(momentum); }
	float GetMass() { return rigidBody == nullptr ? std::numeric_limits<float>::max() : rigidBody->GetMass(); }
	Shape* GetShape() { return shape.get(); }
	vec3 GetVelocity() { return rigidBody == nullptr ? vec3(0) : rigidBody->GetVelocity(); }
	vec3 GetMomentum() { return GetMass() * GetVelocity(); }
	vec3 GetPosition() { return position; }
protected:
	vec3 position;
	std::unique_ptr<Shape> shape;
	std::unique_ptr<RigidBody> rigidBody;
};
