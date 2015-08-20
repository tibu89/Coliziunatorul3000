#pragma once

#define GLM_SWIZZLE 
#include <GL\glm\glm.hpp>
#include <vector>
#include "CollisionShapes.h"
#include "Graphics.h"

struct Contact
{
	int m_iCollidableIndex1, m_iCollidableIndex2;

	glm::vec3 m_ContactNormal;
	glm::vec3 m_ContactPoint;
	float m_Penetration;
};

class ContactGenerator
{
private:
    //PhysicsEngine *m_PhysicsEngine;

	std::vector<Contact> m_Contacts;
	unsigned int m_NumContacts;
	unsigned int m_MaxContacts;

	static glm::vec3 cubeVertices[];
public:
	//ContactGenerator(PhysicsEngine *_physicsEngine, unsigned int _maxContacts = 256 * 256);
	void ClearContacts(){m_NumContacts = 0;}

	void CheckAndAddContact(const Collidable &_collidable1, const Collidable &_collidable2);
    void CheckAndAddContactPlaneCube(const Collidable &_collidable1, const Collidable &_collidable2);

	void DebugContacts( Graphics* graphics );
};