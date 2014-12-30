#pragma once

#include <GL\glm\glm.hpp>
#include <vector>
#include "CollisionShapes.h"

class Contact
{
	PrimitiveShape *shape1, *shape2;

	glm::vec3 contactNormal;
	float penetration;

public:
	Contact() : shape1(NULL), shape2(NULL), contactNormal(glm::vec3(0.f, 1.f, 0.f)), penetration(0.f){}
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
};