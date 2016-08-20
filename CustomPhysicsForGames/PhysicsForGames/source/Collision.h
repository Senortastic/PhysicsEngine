#pragma once
#include "../glm/glm.hpp"

using namespace glm;
class PhysicsObject;
class Plane;

class Collision
{
	Collision() = delete;
public:
	static bool Detect(PhysicsObject* object1, PhysicsObject* object2);
private:
	//plane collision
	static bool PointToPlane(vec3 point, Plane* plane);
	static bool PlaneToSphere(PhysicsObject* object1, PhysicsObject* object2);
	static bool PlaneToAABB(PhysicsObject* object1, PhysicsObject* object2);
	static bool PlaneToPlane(PhysicsObject* object1, PhysicsObject* object2);
	//sphere collision
	static bool SphereToPlane(PhysicsObject* object1, PhysicsObject* object2);
	static bool SphereToSphere(PhysicsObject* object1, PhysicsObject* object2);
	static bool SphereToAABB(PhysicsObject* object1, PhysicsObject* object2);
	//aabb collision
	static bool AABBToPlane(PhysicsObject* object1, PhysicsObject* object2);
	static bool AABBToSphere(PhysicsObject* object1, PhysicsObject* object2);
	static bool AABBToAABB(PhysicsObject* object1, PhysicsObject* object2);
};