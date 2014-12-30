#pragma once

#include "RigidBody.h"

struct PrimitiveShape
{
	RigidBody *body;

	PrimitiveShape(RigidBody *_body = NULL) : body(_body) {}
};

struct CubeShape : PrimitiveShape
{
	glm::vec3 halfSize;

	CubeShape(RigidBody *_body = NULL) : PrimitiveShape(_body) {halfSize = glm::vec3(0.5f, 0.5f, 0.5f);}
};

struct PlaneShape : PrimitiveShape
{
	glm::vec3 normal;
	float offset;

	PlaneShape(float _offset = 0.0f, const glm::vec3 &_normal = glm::vec3(0.0f, 1.0f, 0.0f)) : PrimitiveShape(), normal(_normal), offset(_offset){}
};