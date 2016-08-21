#include "Collision.h"
#include <algorithm>
#include "PhysicsObject.h"

void Seperate(PhysicsObject* object1, PhysicsObject* object2, float overlap, vec3 normal)
{
	float totalMass = object1->GetMass() + object2->GetMass();
	if (totalMass < object1->GetMass() || totalMass < object2->GetMass())
	{
		totalMass = std::numeric_limits<float>::max();
	}

	float massRatio1 = object1->GetMass() / totalMass;
	float massRatio2 = object2->GetMass() / totalMass;

	glm::vec3 separationVector = normal * overlap;
	object1->AddPosition(separationVector * massRatio2);
	object2->AddPosition(-separationVector * massRatio1);
}

void Respond(PhysicsObject* object1, PhysicsObject* object2, float overlap, vec3 normal)
{
	Seperate(object1, object2, overlap, normal);
	const float energyLoss = 0.5f;

	vec3 relativeVelocity = object2->GetVelocity() - object1->GetVelocity();
	float velocityAlongNormal = dot(relativeVelocity, normal);
	float impuseAmount = -(1 + energyLoss) * velocityAlongNormal;
	impuseAmount /= (1 / object1->GetMass()) + (1 / object2->GetMass());

	vec3 impulse = impuseAmount * normal;
	if (object2->HasRigidBody())
	{
		object2->AddVelocity(1 / object2->GetMass() * impulse);
	}
	if (object1->HasRigidBody())
	{
		object1->AddVelocity(1 / object1->GetMass() * -impulse);
	}
}

bool Collision::Detect(PhysicsObject* object1, PhysicsObject* object2)
{
	if (object1->GetShape() == nullptr || object2->GetShape() == nullptr) return false;
	if (object1->HasRigidBody() == false && object2->HasRigidBody() == false) return false;

	int shape1_ID = object1->GetShape()->GetShapeType();
	int shape2_ID = object2->GetShape()->GetShapeType();

	int collisionFunctionIndex = shape1_ID * Shape::GetShapeCount() + shape2_ID;

	switch (collisionFunctionIndex)
	{
	case 0:
		PlaneToPlane(object1, object2);
		break;
	case 1:
		PlaneToSphere(object1, object2);
		break;
	case 2:
		PlaneToAABB(object1, object2);
		break;
	case 3:
		SphereToPlane(object1, object2);
		break;
	case 4:
		SphereToSphere(object1, object2);
		break;
	case 5:
		SphereToAABB(object1, object2);
		break;
	case 6:
		AABBToPlane(object1, object2);
		break;
	case 7:
		AABBToSphere(object1, object2);
		break;
	case 8:
		AABBToAABB(object1, object2);
		break;
	default:
		break;
	}
	return false;
}

bool Collision::PointToPlane(vec3 _point, Plane* _plane)
{
	return dot(_point, _plane->GetNormal()) < 0;
}

bool Collision::PlaneToSphere(PhysicsObject* _planeObject, PhysicsObject* _sphereObject)
{

	const auto pPlane = static_cast<Plane*>(_planeObject->GetShape());
	const auto pSphere = static_cast<Sphere*>(_sphereObject->GetShape());

	const vec3 sphereVector = _sphereObject->GetPosition();
	const vec3 planeNormal = pPlane->GetNormal();

	float sphereDistanceAlongPlaneNormal = glm::dot(sphereVector, planeNormal);
	float overlap = sphereDistanceAlongPlaneNormal - pPlane->GetDistance() - pSphere->GetRadius();
	if (overlap < 0)
	{
		Respond(_planeObject, _sphereObject, overlap, planeNormal);
		return true;
	}

	return false;
}

bool Collision::PlaneToAABB(PhysicsObject* _planeObject, PhysicsObject* _AABBObject)
{

	const auto pPlane = static_cast<Plane*>(_planeObject->GetShape());
	const auto pAABB = static_cast<AABB*>(_AABBObject->GetShape());

	vec3 AABBPos = _AABBObject->GetPosition();
	vec3 minPos = AABBPos - pAABB->GetSize();
	vec3 maxPos = AABBPos + pAABB->GetSize();

	float minPointToDistanceAlongPlaneNormal = dot(minPos, pPlane->GetNormal()) - pPlane->GetDistance();
	float maxPointToDistanceAlongPlaneNormal = dot(maxPos, pPlane->GetNormal()) - pPlane->GetDistance();

	float overlap = std::min(minPointToDistanceAlongPlaneNormal, maxPointToDistanceAlongPlaneNormal);

	if (overlap < 0)
	{
		Respond(_planeObject, _AABBObject, overlap, pPlane->GetNormal());
		return true;
	}

	return false;
}

bool Collision::PlaneToPlane(PhysicsObject* _planeObject1, PhysicsObject* _planeObject2)
{
	return false;
}

bool Collision::SphereToSphere(PhysicsObject* _sphereObject1, PhysicsObject* _sphereObject2)
{
	const auto pSphere1 = static_cast<Sphere*>(_sphereObject1->GetShape());
	const auto pSphere2 = static_cast<Sphere*>(_sphereObject2->GetShape());

	glm::vec3 directionVector = _sphereObject2->GetPosition() - _sphereObject1->GetPosition();
	float centerDistance = glm::length(directionVector);
	float radiusDistance = pSphere1->GetRadius() + pSphere2->GetRadius();

	float overlap = centerDistance - radiusDistance;

	if (overlap < 0)
	{
		Respond(_sphereObject1, _sphereObject2, overlap, glm::normalize(directionVector));
		return true;
	}

	return false;
}

bool Collision::SphereToAABB(PhysicsObject* _sphereObject, PhysicsObject* _AABBObject)
{
	const auto pSphere = static_cast<Sphere*>(_sphereObject->GetShape());
	const auto pAABB = static_cast<AABB*>(_AABBObject->GetShape());

	glm::vec3 minPos = -pAABB->GetSize();
	glm::vec3 maxPos = pAABB->GetSize();

	glm::vec3 distance = _sphereObject->GetPosition() - _AABBObject->GetPosition();
	glm::vec3 clampedPoint = distance;

	if (distance.x < minPos.x)
		clampedPoint.x = minPos.x;
	else if (distance.x > maxPos.x)
		clampedPoint.x = maxPos.x;

	if (distance.y < minPos.y)
		clampedPoint.y = minPos.y;
	else if (distance.y > maxPos.y)
		clampedPoint.y = maxPos.y;

	if (distance.z < minPos.z)
		clampedPoint.z = minPos.z;
	else if (distance.z > maxPos.z)
		clampedPoint.z = maxPos.z;

	glm::vec3 clampedDistance = distance - clampedPoint;

	float overlap = glm::length(clampedDistance) - pSphere->GetRadius();
	if (overlap < 0)
	{
		Respond(_sphereObject, _AABBObject, -overlap, glm::normalize(clampedDistance));
		return true;
	}

	return false;
}

bool Collision::AABBToAABB(PhysicsObject* _AABBObject1, PhysicsObject* _AABBObject2)
{
	const auto pAABB1 = static_cast<AABB*>(_AABBObject1->GetShape());
	const auto pAABB2 = static_cast<AABB*>(_AABBObject2->GetShape());

	glm::vec3 box1Pos = _AABBObject1->GetPosition();
	glm::vec3 box1Extents = pAABB1->GetSize();

	glm::vec3 box2Pos = _AABBObject2->GetPosition();
	glm::vec3 box2Extents = pAABB2->GetSize();

	glm::vec3 boxDelta = box2Pos - box1Pos;
	glm::vec3 boxExtentsCombined = box1Extents + box2Extents;

	float xOverlap = std::abs(boxDelta.x) - boxExtentsCombined.x;
	float yOverlap = std::abs(boxDelta.y) - boxExtentsCombined.y;
	float zOverlap = std::abs(boxDelta.z) - boxExtentsCombined.z;


	if (xOverlap <= 0 && yOverlap <= 0 && zOverlap <= 0)
	{
		float minOverlap = xOverlap;
		minOverlap = yOverlap <= 0 ? std::max(minOverlap, yOverlap) : minOverlap;
		minOverlap = zOverlap <= 0 ? std::max(minOverlap, zOverlap) : minOverlap;

		glm::vec3 separationNormal(0);

		if (xOverlap == minOverlap) separationNormal.x = std::signbit(boxDelta.x) ? -1.f : 1.f;
		else if (yOverlap == minOverlap) separationNormal.y = std::signbit(boxDelta.y) ? -1.f : 1.f;
		else if (zOverlap == minOverlap) separationNormal.z = std::signbit(boxDelta.z) ? -1.f : 1.f;

		Respond(_AABBObject1, _AABBObject2, minOverlap, separationNormal);

		return true;
	}

	return false;
}