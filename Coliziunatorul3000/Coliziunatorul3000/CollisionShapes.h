#pragma once

#include "RigidBody.h"

enum ShapeType
{
	CUBE = 0,
	PLANE
};

struct PlaneShape
{
	glm::vec3 normal;
	float offset;

	PlaneShape(float _offset = 0.0f, const glm::vec3 &_normal = glm::vec3(0.0f, 1.0f, 0.0f)){}
};

struct Collidable
{
	int m_iRigidBodyIndex;
	ShapeType m_iShapeType;

	glm::vec4 m_vData; //half size for CUBE, normal + dist for PLANE
};