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
	static bool PlaneToSphere(PhysicsObject* plane, PhysicsObject* sphere);
	static bool PlaneToAABB(PhysicsObject* plane, PhysicsObject* AABB);
	static bool PlaneToPlane(PhysicsObject* plane1, PhysicsObject* plane2);
	//sphere collision
	static bool SphereToPlane(PhysicsObject* sphere, PhysicsObject* plane) { return PlaneToSphere(plane, sphere); }
	static bool SphereToSphere(PhysicsObject* sphere1, PhysicsObject* sphere2);
	static bool SphereToAABB(PhysicsObject* sphere, PhysicsObject* AABB);
	//aabb collision
	static bool AABBToPlane(PhysicsObject* AABB, PhysicsObject* plane) { return PlaneToAABB(plane, AABB); }
	static bool AABBToSphere(PhysicsObject* AABB, PhysicsObject* sphere) { return SphereToAABB(sphere, AABB); }
	static bool AABBToAABB(PhysicsObject* AABB1, PhysicsObject* AABB2);
};