#ifndef SOUND_PROGRAMMING_H_
#define SOUND_PROGRAMMING_H_

#include "Application.h"
#include "Camera.h"
#include "Render.h"
#include "source\PhysicsScene.h"

#include <PxPhysicsAPI.h>
#include <PxScene.h>
#include <random>

using namespace physx;
class Physics : public Application
{
public:
    virtual bool startup();
    virtual void shutdown();
    virtual bool update();
    virtual void draw();
	void MakeRope(int length);
	void SetupScene();

	float deltaTime;
	float currentTime;
	float lastFrameTime;
	
	std::unique_ptr<PhysicsScene> physicsScene;
	std::default_random_engine generator;
	std::uniform_real_distribution<float> velocityDistribution;
	std::uniform_real_distribution<float> massDistribution;

    void renderGizmos(PxScene* physics_scene);

    Renderer* m_renderer;
    FlyCamera m_camera;
    float m_delta_time;
    PxExtendedVec3 startingPosition = PxExtendedVec3(0,2,0);
private:
	void CreateBoundary(PhysicsScene* physicsScene, float tableSize, float borderHeight);
	void CreateSpheres(PhysicsScene* physicsScene, int sphereCount, float spacing);
	void CreateAABBs(PhysicsScene* physicsScene, int aabbCount, float spacing);
};

#endif //CAM_PROJ_H_
