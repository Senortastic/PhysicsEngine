#include "Collision.h"

bool Collision::Detect(PhysicsObject * object1, PhysicsObject * object2)
{
	return false;
}

bool Collision::PointToPlane(vec3 point, Plane * plane)
{
	return false;
}

bool Collision::PlaneToSphere(PhysicsObject * object1, PhysicsObject * object2)
{
	return false;
}

bool Collision::PlaneToAABB(PhysicsObject * object1, PhysicsObject * object2)
{
	return false;
}

bool Collision::PlaneToPlane(PhysicsObject * object1, PhysicsObject * object2)
{
	return false;
}

bool Collision::SphereToPlane(PhysicsObject * object1, PhysicsObject * object2)
{
	return false;
}

bool Collision::SphereToSphere(PhysicsObject * object1, PhysicsObject * object2)
{
	return false;
}

bool Collision::SphereToAABB(PhysicsObject * object1, PhysicsObject * object2)
{
	return false;
}

bool Collision::AABBToPlane(PhysicsObject * object1, PhysicsObject * object2)
{
	return false;
}

bool Collision::AABBToSphere(PhysicsObject * object1, PhysicsObject * object2)
{
	return false;
}

bool Collision::AABBToAABB(PhysicsObject * object1, PhysicsObject * object2)
{
	return false;
}
