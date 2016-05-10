#include "PhysicsScene.h"

void PhysicsScene::AddActor(PhysicsObject* actor)
{
	actors.push_back(actor);
}

void PhysicsScene::Update()
{
	for (auto iter = actors.begin(); iter != actors.end(); ++iter)
	{
		(*iter)->Update(gravity, timeStep);
	}
}

