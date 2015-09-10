#pragma once

#define GLM_SWIZZLE 
#include <GL\glm\glm.hpp>
#include <vector>
#include "CollisionShapes.h"
#include "RigidBody.h"
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
	std::vector<CollisionData> m_Manifolds;
	unsigned int m_NumManifolds;
	unsigned int m_MaxManifolds;

	std::vector<RigidBody> *m_RigidBodies;

	static glm::vec3 cubeVertices[];
	static glm::vec3 cubeFaceNormals[];
	static unsigned char cubeFaceVertexIndices[];
public:
	ContactGenerator(std::vector<RigidBody> *_rigidBodies, unsigned int _maxContacts = 256 * 256);
	void ClearContacts(){m_NumManifolds = 0;}

	void CheckAndAddContact(const Collidable &_collidable1, const Collidable &_collidable2);
    void CheckAndAddContactPlaneCube(const Collidable &_collidable1, const Collidable &_collidable2);

	void DebugContacts( Graphics* graphics );

private:
	int GetBestCubeFaceToDirection(const glm::quat &orientation, const glm::vec3 &dir);
};