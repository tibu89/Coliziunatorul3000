#pragma once

#define GLM_SWIZZLE 
#include <GL\glm\glm.hpp>
#include <vector>
#include "CollisionShapes.h"
#include "Graphics.h"

struct Contact
{
	//for cube: 0-7 vertices, 8-13 faces, 13-25 edges
	int m_iFeatureIndex1, m_iFeatureIndex2;

	glm::vec3 m_ContactNormal;
	glm::vec3 m_ContactPoint;
	float m_Penetration;
};

struct CollisionData
{
	int m_iCollidableIndex1, m_iCollidableIndex2;
	int m_iNumContacts;

	Contact contacts[4];
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