#pragma once

#define GLM_SWIZZLE 
#include <GL\glm\glm.hpp>
#include <vector>
#include "CollisionShapes.h"

#include "Graphics.h"

struct Contact
{
	const PrimitiveShape *shape1, *shape2;

	glm::vec3 contactNormal;
	glm::vec3 contactPoint;
	float penetration;

public:
	Contact() : shape1(NULL), shape2(NULL), contactNormal(glm::vec3(0.f, 1.f, 0.f)), contactPoint(glm::vec3(0.f, 0.f, 0.f)), penetration(0.f){}

	Contact( const PrimitiveShape* _s1, const PrimitiveShape* _s2, glm::vec3 _cN, glm::vec3 _cP, float _pen )
	{
		shape1 = _s1;
		shape2 = _s2;

		contactNormal = _cN;
		contactPoint = _cP;

		penetration = _pen;
	}
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