#pragma once
#include <vector>
#include "SphereClass.h"

class PhysicsScene
{
public:
	vec3 gravity;
	float timeStep;
	std::vector<PhysicsObject*> actors;
	void AddActor(PhysicsObject* actor);
	void Update();
	void DebugScene();
	void AddGizmos();
};