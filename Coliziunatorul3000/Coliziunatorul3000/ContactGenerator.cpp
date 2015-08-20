#include "ContactGenerator.h"
#include <gl\glm\gtc\matrix_access.hpp>
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

/*ContactGenerator::ContactGenerator(PhysicsEngine *_physicsEngine, unsigned int _maxContacts)
{
    m_PhysicsEngine = _physicsEngine;
	m_MaxContacts = _maxContacts;
	m_Contacts.resize(m_MaxContacts);
	m_NumContacts = 0;
}*/

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
	/*for( unsigned int i = 0; i < numContacts; i++ )
	{
		graphics->DrawDebugPoint( contacts[i].contactPoint );
	}*/
}