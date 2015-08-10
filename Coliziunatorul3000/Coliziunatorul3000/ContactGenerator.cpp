#include "ContactGenerator.h"
#include <gl\glm\gtc\matrix_access.hpp>
#include <iostream>

float ProjectToAxis(const CubeShape& cubeShape, const glm::vec3& axis)
{
	const glm::mat4& trMatrix = cubeShape.body->GetTransformMatrix();

	return 
		abs(glm::dot(glm::vec3(glm::column(trMatrix, 0)), axis)) * cubeShape.halfSize.x +
		abs(glm::dot(glm::vec3(glm::column(trMatrix, 1)), axis)) * cubeShape.halfSize.y +
		abs(glm::dot(glm::vec3(glm::column(trMatrix, 2)), axis)) * cubeShape.halfSize.z;
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

ContactGenerator::ContactGenerator(unsigned int _maxContacts)
{
	maxContacts = _maxContacts;
	contacts.resize(maxContacts);
	numContacts = 0;
}

void ContactGenerator::CheckAndAddContact(const PlaneShape &planeShape, const CubeShape &cubeShape)
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
}

void ContactGenerator::DebugContacts( Graphics *graphics )
{
	for( unsigned int i = 0; i < numContacts; i++ )
	{
		graphics->DrawDebugPoint( contacts[i].contactPoint );
	}
}