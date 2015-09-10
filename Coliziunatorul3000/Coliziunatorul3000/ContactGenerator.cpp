#include "ContactGenerator.h"
#include <gl\glm\gtc\matrix_access.hpp>
#include <gl\glm\gtx\quaternion.hpp>
#include <iostream>

float ProjectToAxis(const glm::mat4& _trMatrix, const glm::vec3& _halfSize, const glm::vec3& _axis)
{
	return 
        abs(glm::dot(glm::vec3(glm::column(_trMatrix, 0)), _axis)) * _halfSize.x +
        abs(glm::dot(glm::vec3(glm::column(_trMatrix, 1)), _axis)) * _halfSize.y +
        abs(glm::dot(glm::vec3(glm::column(_trMatrix, 2)), _axis)) * _halfSize.z;
}

glm::vec3 ContactGenerator::cubeVertices[] = {
	glm::vec3(-0.5f, -0.5f, -0.5f),
	glm::vec3(-0.5f, -0.5f,  0.5f),
	glm::vec3(-0.5f,  0.5f, -0.5f),
	glm::vec3(-0.5f,  0.5f,  0.5f),
	glm::vec3( 0.5f, -0.5f, -0.5f),
	glm::vec3( 0.5f, -0.5f,  0.5f),
	glm::vec3( 0.5f,  0.5f, -0.5f),
	glm::vec3( 0.5f,  0.5f,  0.5f)
};

glm::vec3 ContactGenerator::cubeFaceNormals[] = {
	glm::vec3( 1.f, 0.f, 0.f),
	glm::vec3(-1.f, 0.f, 0.f),
	glm::vec3( 0.f, 1.f, 0.f),
	glm::vec3( 0.f,-1.f, 0.f),
	glm::vec3( 0.f, 0.f, 1.f),
	glm::vec3( 0.f, 0.f,-1.f),
};

unsigned char ContactGenerator::cubeFaceVertexIndices[] = {
	4, 6, 7, 5,
	0, 1, 3, 2,
	2, 3, 7, 6,
	0, 4, 5, 1,
	1, 5, 7, 3,
	0, 2, 6, 4,
};

ContactGenerator::ContactGenerator(std::vector<RigidBody> *_rigidBodies, unsigned int _maxContacts)
{
	m_RigidBodies = _rigidBodies;
	m_MaxManifolds = _maxContacts;
	m_Manifolds.resize(m_MaxManifolds);
	m_NumManifolds = 0;
}

int ContactGenerator::GetBestCubeFaceToDirection(const glm::quat &orientation, const glm::vec3 &dir)
{
	int bestFaceIndex = -1;
	glm::mat3 rotationMatrix = glm::toMat3(orientation);

	float minF = FLT_MAX;

	//looking for face most facing direction, so for minimum dot product
	//!!! assuming normalized vectors !!!
	for(unsigned short i = 0; i < 6; i++)
	{
		float f = glm::dot(rotationMatrix * cubeFaceNormals[i], dir);

		if( f < minF )
		{
			minF = f;
			bestFaceIndex = i;
		}
	}

	assert(bestFaceIndex != -1);
	return bestFaceIndex;
}

void ContactGenerator::CheckAndAddContact(const Collidable &_collidable1, const Collidable &_collidable2)
{
    if(_collidable1.m_iShapeType == ShapeType::PLANE && _collidable2.m_iShapeType == ShapeType::CUBE)
    {
        CheckAndAddContactPlaneCube(_collidable1, _collidable2); return;
    }
    
    if(_collidable2.m_iShapeType == ShapeType::PLANE && _collidable1.m_iShapeType == ShapeType::CUBE)
    {
        CheckAndAddContactPlaneCube(_collidable2, _collidable1); return;
    }
}

void ContactGenerator::CheckAndAddContactPlaneCube(const Collidable &_collidable1, const Collidable &_collidable2)
{
	if(m_NumManifolds >= m_MaxManifolds)
	{
		std::cerr<<"Max contacts reached!!!\n";
		return;
	}

	glm::vec3 planeNormal = _collidable1.m_vData.xyz;
	float planeDist = _collidable1.m_vData.w;
	RigidBody &body = m_RigidBodies->at(_collidable2.m_iRigidBodyIndex);
	glm::mat4 cubeTrMatrix = body.GetTransformMatrix();
	glm::vec3 cubeHalfSize = _collidable2.m_vData.xyz;

	float projectedRadius = ProjectToAxis(cubeTrMatrix, cubeHalfSize, planeNormal);

	if(glm::dot(planeNormal, body.GetPosition()) - projectedRadius > planeDist)
	{
		return; //cube too far to potentially contact
	}

	int incidentFaceIndex = GetBestCubeFaceToDirection(m_RigidBodies->at(_collidable2.m_iRigidBodyIndex).GetOrientation(), planeNormal);
	glm::vec4 currentVertex;

	CollisionData &collisionData = m_Manifolds[m_NumManifolds++];
	collisionData.m_iNumContacts = 0;

	for(unsigned short faceVertIndex = incidentFaceIndex * 4; faceVertIndex < incidentFaceIndex * 4 + 4; faceVertIndex++)
	{
		currentVertex = glm::vec4(cubeVertices[cubeFaceVertexIndices[faceVertIndex]], 1.f);
		
		currentVertex = cubeTrMatrix * currentVertex;

		Contact &newContact = collisionData.contacts[collisionData.m_iNumContacts++];

		newContact.m_ContactNormal = planeNormal;
		newContact.m_ContactPoint = currentVertex.xyz;
		newContact.m_iFeatureIndex1 = faceVertIndex;
		newContact.m_iFeatureIndex2 = -1;
		newContact.m_Penetration = 0.f;
	}
}

/*void ContactGenerator::CheckAndAddContact(const PlaneShape &planeShape, const CubeShape &cubeShape)
{
	if( numContacts >= maxContacts )
	{
		return;
	}

	//midphase: (?)
	float projectedRadius = ProjectToAxis(cubeShape, planeShape.normal);
	if(glm::dot(planeShape.normal, cubeShape.body->GetPosition()) - projectedRadius > planeShape.offset)
	{
		return; //cube too far to potentially contact
	}

	glm::mat4 sizeTransform = glm::scale(cubeShape.halfSize * 2.f);

	glm::vec3 currentVertex;

	for(unsigned int i = 0; i < 8 && numContacts < maxContacts; i++)
	{
		currentVertex = ( cubeShape.body->GetTransformMatrix() * sizeTransform * glm::vec4(cubeVertices[i], 1.f) ).xyz;

		float distance = glm::dot( planeShape.normal, currentVertex );

		if( distance < planeShape.offset )
		{
			float penetration = planeShape.offset - distance;

			glm::vec3 contactPoint = planeShape.normal * (penetration / 2) + currentVertex;

			Contact contact;
						
			contacts[numContacts++] = Contact( &planeShape, &cubeShape, planeShape.normal, contactPoint, penetration );
		}
	}
}*/

void ContactGenerator::DebugContacts( Graphics *graphics )
{
	for(unsigned int i = 0; i < m_NumManifolds; i++)
	{
		CollisionData &cdata = m_Manifolds[i];
		for(unsigned short j = 0; j < cdata.m_iNumContacts; j++)
		{
			graphics->DrawDebugPoint(cdata.contacts[j].m_ContactPoint);
		}
	}
}