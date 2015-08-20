#pragma once

#include "RigidBody.h"

enum ShapeType
{
	CUBE = 0,
	PLANE
};

struct Collidable
{
	int m_iRigidBodyIndex;
	ShapeType m_iShapeType;

	glm::vec4 m_vData; //half size for CUBE, normal + dist for PLANE
};