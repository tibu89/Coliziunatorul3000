#pragma once

#include <vector>
#include <GL\glm\glm.hpp>
#include "RigidBody.h"
#include "ContactGenerator.h"

typedef int RigidBodyID;

class PhysicsEngine
{
private:
	std::vector<RigidBody> m_DynamicBodies;
    std::vector<Collidable> m_Collidables;

    ContactGenerator *m_ContactGenerator;

public:

    PhysicsEngine()
    {
        //m_ContactGenerator = new ContactGenerator(this, 10000);
    }

	void Update(float _fDt);

	RigidBodyID AddCube(glm::vec3 _pos, glm::quat _orientation, glm::vec3 _halfSize);
};