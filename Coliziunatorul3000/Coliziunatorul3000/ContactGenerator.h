#pragma once

#define GLM_SWIZZLE 
#include <GL\glm\glm.hpp>
#include <vector>
#include "CollisionShapes.h"

#include "Graphics.h"

struct Contact
{
	int m_iCollidableIndex1, m_iCollidableIndex2;

	glm::vec3 contactNormal;
	glm::vec3 contactPoint;
	float penetration;
};

class ContactGenerator
{
	std::vector<Contact> contacts;
	unsigned int numContacts;
	unsigned int maxContacts;

	static glm::vec3 cubeVertices[];
public:
	ContactGenerator(unsigned int _maxContacts);
	void ClearContacts(){numContacts = 0;}

	void CheckAndAddContact(const PlaneShape &planeShape, const CubeShape &cubeShape);
	void CheckAndAddContact(const CubeShape &cubeShape1, const CubeShape &cubeShape2);

	void DebugContacts( Graphics* graphics );
};