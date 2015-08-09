#pragma once

#include <vector>
#include "RigidBody.h"
#include "ContactGenerator.h"

typedef int RigidBodyID;

class PhysicsEngine
{
private:
	std::vector<RigidBody> m_DynamicBodies;
	std::vector<PrimitiveShape> m_DynamicPrimitives;

	std::vector<PlaneShape> m_Planes;

public:

	void Update(float _fDt);

	RigidBodyID AddCube(glm::vec3 _pos, glm::quat _orientation, glm::vec3 _halfSize);

};