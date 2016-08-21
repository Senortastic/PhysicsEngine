#include "PhysicsScene.h"
#include "RigidBody.h"
#include "PhysicsObject.h"
#include "SpringJoint.h"

void PhysicsScene::Update(float deltaTime)
{
	const float DampingCoeffecient = 0.2f;

	for (auto& PysObj : actors)
	{
		PysObj->AddForce(DampingCoeffecient * -PysObj->GetVelocity() * deltaTime);
	}

	for (auto& PysObj : actors)
	{
		PysObj->Update(gravity, deltaTime);
	}

	CheckCollisions();
}

void PhysicsScene::Draw()
{
	for (auto& PysObj : actors)
	{
		PysObj->Draw();
	}
}

std::shared_ptr<PhysicsObject> PhysicsScene::AddPlaneStatic(glm::vec3 normal, float distance)
{
	return AddPlane(normal, distance);
}

std::shared_ptr<PhysicsObject> PhysicsScene::AddSphereStatic(glm::vec3 position, float radius)
{
	return AddSphere(position, radius);
}

std::shared_ptr<PhysicsObject> PhysicsScene::AddAABBStatic(glm::vec3 position, glm::vec3 extents)
{
	return AddAABB(position, extents);
}

std::shared_ptr<PhysicsObject> PhysicsScene::AddPlaneDynamic(glm::vec3 normal, float distance, float mass, glm::vec3 velocity)
{
	return AddPlane(normal, distance, new RigidBody(mass, velocity));
}

std::shared_ptr<PhysicsObject> PhysicsScene::AddSphereDynamic(glm::vec3 position, float radius, float mass, glm::vec3 velocity)
{
	return AddSphere(position, radius, new RigidBody(mass, velocity));
}

std::shared_ptr<PhysicsObject> PhysicsScene::AddAABBDynamic(glm::vec3 position, glm::vec3 extents, float mass, glm::vec3 velocity)
{
	return AddAABB(position, extents, new RigidBody(mass, velocity));
}

std::shared_ptr<PhysicsObject> PhysicsScene::AddSpring(std::shared_ptr<PhysicsObject> connection1, std::shared_ptr<PhysicsObject> connection2, float springCoefficient, float damping, float restingDistance)
{
	auto pSpring = std::make_shared<SpringJoint>(connection1, connection2, springCoefficient, damping, restingDistance);
	AddActor(pSpring);
	return pSpring;
}

std::shared_ptr<PhysicsObject> PhysicsScene::AddPlane(glm::vec3 normal, float distance, RigidBody* pRigidBody)
{
	auto pPlane = std::make_shared<PhysicsObject>(glm::vec3(0), new Plane(normal, distance), pRigidBody);
	AddActor(pPlane);
	return pPlane;
}

std::shared_ptr<PhysicsObject> PhysicsScene::AddSphere(glm::vec3 position, float radius, RigidBody* pRigidBody)
{
	auto pSphere = std::make_shared<PhysicsObject>(position, new Sphere(radius), pRigidBody);
	AddActor(pSphere);
	return pSphere;
}

std::shared_ptr<PhysicsObject> PhysicsScene::AddAABB(glm::vec3 position, glm::vec3 extents, RigidBody* pRigidBody)
{
	auto pBox = std::make_shared<PhysicsObject>(position, new AABB(extents), pRigidBody);
	AddActor(pBox);
	return pBox;
}

void PhysicsScene::AddActor(std::shared_ptr<PhysicsObject> physicsObject)
{
	actors.push_back(physicsObject);
}

void PhysicsScene::SetGravity(vec3 gravity)
{
	this->gravity = gravity;
}

void PhysicsScene::CheckCollisions()
{
	for (auto iter = std::begin(actors); iter != std::end(actors); ++iter)
	{
		for (auto iter2 = std::next(iter); iter2 != std::end(actors); ++iter2)
		{
			Collision::Detect(iter->get(), iter2->get());
		}
	}
}