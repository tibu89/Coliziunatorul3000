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
	glm::vec3(-1.f, -1.f, -1.f),
	glm::vec3(-1.f, -1.f,  1.f),
	glm::vec3(-1.f,  1.f, -1.f),
	glm::vec3(-1.f,  1.f,  1.f),
	glm::vec3( 1.f, -1.f, -1.f),
	glm::vec3( 1.f, -1.f,  1.f),
	glm::vec3( 1.f,  1.f, -1.f),
	glm::vec3( 1.f,  1.f,  1.f)
};

ContactGenerator::ContactGenerator(unsigned int _maxContacts)
{
	maxContacts = _maxContacts;
	contacts.resize(maxContacts);
	numContacts = 0;
}

void ContactGenerator::CheckAndAddContact(const PlaneShape &planeShape, const CubeShape &cubeShape)
{
	//midphase: (?)
	float projectedRadius = ProjectToAxis(cubeShape, planeShape.normal);
	if(glm::dot(planeShape.normal, cubeShape.body->GetPosition()) - projectedRadius > planeShape.offset)
	{
		return; //cube too far to potentially contact
	}

	glm::vec4 transformedVertices[8];
	glm::mat4 sizeTransform = glm::scale(cubeShape.halfSize * 2.f);

	for(unsigned int i = 0; i < 8; i++)
	{
		transformedVertices[i] = cubeShape.body->GetTransformMatrix() * sizeTransform * glm::vec4(cubeVertices[i], 1.f);
	}
}