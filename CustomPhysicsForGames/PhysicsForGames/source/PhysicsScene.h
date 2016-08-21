#pragma once
#include <memory>
#include <vector>
#include "Collision.h"

using namespace glm;

class RigidBody;

class PhysicsScene
{
public:
	PhysicsScene() : PhysicsScene(glm::vec3(0)) {}
	PhysicsScene(glm::vec3 offset) : offset(offset) {}

	void Update(float deltaTime);
	void Draw();

	void SetGravity(vec3 gravity);
	std::shared_ptr<PhysicsObject> AddPlaneStatic(glm::vec3 normal, float distance);
	std::shared_ptr<PhysicsObject> AddSphereStatic(glm::vec3 position, float radius);
	std::shared_ptr<PhysicsObject> AddAABBStatic(glm::vec3 position, glm::vec3 extents);
	std::shared_ptr<PhysicsObject> AddPlaneDynamic(glm::vec3 normal, float distance, float mass, glm::vec3 velocity);
	std::shared_ptr<PhysicsObject> AddSphereDynamic(glm::vec3 position, float radius, float mass, glm::vec3 velocity);
	std::shared_ptr<PhysicsObject> AddAABBDynamic(glm::vec3 position, glm::vec3 extents, float mass, glm::vec3 velocity);
	std::shared_ptr<PhysicsObject> AddSpring(std::shared_ptr<PhysicsObject> connection1, std::shared_ptr<PhysicsObject> connection2, float springCoefficient, float damping, float restingDistance = 0);

private:
	std::shared_ptr<PhysicsObject> AddPlane(glm::vec3 normal, float distance, RigidBody* rigidBody = nullptr);
	std::shared_ptr<PhysicsObject> AddSphere(glm::vec3 position, float radius, RigidBody* rigidBody = nullptr);
	std::shared_ptr<PhysicsObject> AddAABB(glm::vec3 position, glm::vec3 extents, RigidBody* rigidBody = nullptr);

	void AddActor(std::shared_ptr<PhysicsObject> pPhysicsObject);
	void CheckCollisions();
	vec3 gravity;
	vec3 offset;
	float timeStep = .001f;
	std::vector<std::shared_ptr<PhysicsObject>>actors;
};