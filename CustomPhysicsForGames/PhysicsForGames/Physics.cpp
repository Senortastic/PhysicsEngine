#include "Physics.h"
#include "source\PhysicsObject.h"
#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"
#include "Gizmos.h"
#include "glm/ext.hpp"
#include "glm/gtc/quaternion.hpp"

#include <functional>

#define Assert(val) if (val){}else{ *((char*)0) = 0;}
#define ArrayCount(val) (sizeof(val)/sizeof(val[0]))

bool Physics::startup()
{
	if (Application::startup() == false)
	{
		return false;
	}

	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	Gizmos::create();

	m_camera = FlyCamera(1280.0f / 720.0f, 10.0f);
	m_camera.setLookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	m_camera.sensitivity = 3;

	m_renderer = new Renderer();
	physicsScene = std::make_unique<PhysicsScene>(vec3(70, 0, 0));
	SetupScene();
	return true;
}

void Physics::shutdown()
{
	delete m_renderer;
	Gizmos::destroy();
	Application::shutdown();
}

bool Physics::update()
{
	if (Application::update() == false)
	{
		return false;
	}

	Gizmos::clear();

	float dt = (float)glfwGetTime();
	m_delta_time = dt;
	glfwSetTime(0.0);

	vec4 white(1);
	vec4 black(0, 0, 0, 1);

	for (int i = 0; i <= 20; ++i) {
	    Gizmos::addLine(vec3(-10 + i, -0.01, -10), vec3(-10 + i, -0.01, 10),
	                    i == 10 ? white : black);
	    Gizmos::addLine(vec3(-10, -0.01, -10 + i), vec3(10, -0.01, -10 + i),
	                    i == 10 ? white : black);
	}

	static bool bPressed = false;
	if (!bPressed && glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
	{
		physicsScene->AddSphereDynamic(vec3(m_camera.world[3]), 1.0f, 1.0f, vec3(m_camera.world[2]) * -25.0f);
		bPressed = true;
	}
	else if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_1) != GLFW_PRESS)
	{
		bPressed = false;
	}

	GLFWwindow* curr_window = glfwGetCurrentContext();
	m_camera.update(m_delta_time);
	physicsScene->Update(m_delta_time);
	return true;
}

void Physics::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);

	m_renderer->RenderAndClear(m_camera.view_proj);
	physicsScene->Draw();
	Gizmos::draw(m_camera.proj, m_camera.view);

	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

void Physics::SetupScene()
{
	physicsScene->SetGravity(glm::vec3(0.0, -9.8, 0.0f));
	physicsScene->AddPlaneStatic(vec3(0, 1, 0), -10);

	physicsScene->AddAABBStatic(vec3(10, -2, 5), vec3(0.5f, 2, 0.5f));
	physicsScene->AddAABBStatic(vec3(-10, -2, 5), vec3(0.5f, 2, 0.5f));
	physicsScene->AddAABBStatic(vec3(-10, -2, -5), vec3(0.5f, 2, 0.5f));
	physicsScene->AddAABBStatic(vec3(10, -2, -5), vec3(0.5f, 2, 0.5f));

	physicsScene->AddAABBStatic(vec3(-5, 0, 0), vec3(6, 0.5f, 6));
	physicsScene->AddAABBStatic(vec3(5, 0, 0), vec3(6, 0.5f, 6));

	physicsScene->AddAABBDynamic(vec3(0, 2, 0), vec3(1, 1, 1), 5, vec3(0));
	physicsScene->AddAABBDynamic(vec3(0, 2, 3), vec3(1, 1, 1), 5, vec3(0));
	physicsScene->AddAABBDynamic(vec3(2, 2, -1), vec3(1, 1, 1), 5, vec3(0));
	physicsScene->AddAABBDynamic(vec3(0, 3, -1), vec3(1, 1, 1), 5, vec3(0));
	CreateRope(7);
}

void Physics::CreateBoundary(PhysicsScene* physicsScene, float tableSize, float borderHeight)
{
	physicsScene->AddAABBStatic(glm::vec3(0, 0.5f, (tableSize / 2) + 1), glm::vec3(tableSize / 2, borderHeight, 1));

	physicsScene->AddAABBStatic(glm::vec3(0, 0.5f, (-tableSize / 2) - 1), glm::vec3(tableSize / 2, borderHeight, 1));

	physicsScene->AddAABBStatic(glm::vec3((tableSize / 2) + 1, 0.5f, 0), glm::vec3(1, borderHeight, tableSize / 2));

	physicsScene->AddAABBStatic(glm::vec3((-tableSize / 2) - 1, 0.5f, 0), glm::vec3(1, borderHeight, tableSize / 2));
}

void Physics::CreateSpheres(PhysicsScene* pPhysicsScene, int sphereCount, float spacing)
{
	auto randVel = std::bind(velocityDistribution, generator);

	for (int i = 0; i < sphereCount; ++i)
	{
		float mass = massDistribution(generator);
		pPhysicsScene->AddSphereDynamic(glm::vec3(-20 + i*spacing, 2 + i, -20 + i*spacing),	std::pow(mass, 0.2f), mass, glm::vec3(randVel(), 0, randVel()));
	}

}

void Physics::CreateAABBs(PhysicsScene* physicsScene, int aabbCount, float spacing)
{
	auto randVel = std::bind(velocityDistribution, generator);
	for (int i = 0; i < aabbCount; i++)
	{
		physicsScene->AddAABBDynamic(glm::vec3(-20 + i*spacing, 6 + i, -20 + i*spacing),	glm::vec3(1, 1, 1),	1, glm::vec3(randVel(), 0, randVel()));
	}

}

void Physics::CreateRope(int length)
{
	auto sphere = physicsScene->AddSphereStatic(vec3(0, 15, 0), 1);
	std::shared_ptr<PhysicsObject> previousSphere;
	previousSphere = sphere;
	for (int i = 0; i < length; i++)
	{
		vec3 newpos(previousSphere->GetPosition().x, previousSphere->GetPosition().y - 1, previousSphere->GetPosition().z);
		auto newSphere = physicsScene->AddSphereDynamic(newpos, 0.25, 5, vec3(0, 0, 0));
		physicsScene->AddSpring(previousSphere, newSphere, 200, 50, 0.5f);

		previousSphere = newSphere;
	}
}

void AddWidget(PxShape* shape, PxRigidActor* actor, vec4 geo_color)
{
	PxTransform full_transform = PxShapeExt::getGlobalPose(*shape, *actor);
	vec3 actor_position(full_transform.p.x, full_transform.p.y, full_transform.p.z);
	glm::quat actor_rotation(full_transform.q.w,
		full_transform.q.x,
		full_transform.q.y,
		full_transform.q.z);
	glm::mat4 rot(actor_rotation);

	mat4 rotate_matrix = glm::rotate(10.f, glm::vec3(7, 7, 7));

	PxGeometryType::Enum geo_type = shape->getGeometryType();

	switch (geo_type)
	{
	case (PxGeometryType::eBOX) : {
		PxBoxGeometry geo;
		shape->getBoxGeometry(geo);
		vec3 extents(geo.halfExtents.x, geo.halfExtents.y, geo.halfExtents.z);
		Gizmos::addAABBFilled(actor_position, extents, geo_color, &rot);
	}
								  break;
	case (PxGeometryType::eCAPSULE) : {
		PxCapsuleGeometry geo;
		shape->getCapsuleGeometry(geo);
		Gizmos::addCapsule(actor_position, geo.halfHeight * 2, geo.radius, 16, 16, geo_color, &rot);
	}
									  break;
	case (PxGeometryType::eSPHERE) : {
		PxSphereGeometry geo;
		shape->getSphereGeometry(geo);
		Gizmos::addSphereFilled(actor_position, geo.radius, 16, 16, geo_color, &rot);
	}
									 break;
	case (PxGeometryType::ePLANE) : { }
									break;
	}
}

void Physics::renderGizmos(PxScene* physics_scene)
{
	PxActorTypeFlags desiredTypes = PxActorTypeFlag::eRIGID_STATIC | PxActorTypeFlag::eRIGID_DYNAMIC;
	PxU32 actor_count = physics_scene->getNbActors(desiredTypes);
	PxActor** actor_list = new PxActor*[actor_count];
	physics_scene->getActors(desiredTypes, actor_list, actor_count);

	vec4 geo_color(1, 0, 0, 1);
	for (int actor_index = 0;
	actor_index < (int)actor_count;
		++actor_index)
	{
		PxActor* curr_actor = actor_list[actor_index];
		if (curr_actor->isRigidActor())
		{
			PxRigidActor* rigid_actor = (PxRigidActor*)curr_actor;
			PxU32 shape_count = rigid_actor->getNbShapes();
			PxShape** shapes = new PxShape*[shape_count];
			rigid_actor->getShapes(shapes, shape_count);

			for (int shape_index = 0;
			shape_index < (int)shape_count;
				++shape_index)
			{
				PxShape* curr_shape = shapes[shape_index];
				AddWidget(curr_shape, rigid_actor, geo_color);
			}

			delete[]shapes;
		}
	}

	delete[] actor_list;

	int articulation_count = physics_scene->getNbArticulations();

	for (int a = 0; a < articulation_count; ++a)
	{
		PxArticulation* articulation;
		physics_scene->getArticulations(&articulation, 1, a);

		int link_count = articulation->getNbLinks();

		PxArticulationLink** links = new PxArticulationLink*[link_count];
		articulation->getLinks(links, link_count);

		for (int l = 0; l < link_count; ++l)
		{
			PxArticulationLink* link = links[l];
			int shape_count = link->getNbShapes();

			for (int s = 0; s < shape_count; ++s)
			{
				PxShape* shape;
				link->getShapes(&shape, 1, s);
				AddWidget(shape, link, geo_color);
			}
		}
		delete[] links;
	}
}

