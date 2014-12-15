#pragma once

#include "RigidBody.h"

struct PrimitiveShape
{
	RigidBody *body;

	PrimitiveShape(RigidBody *_body) : body(_body) {}
	PrimitiveShape() : body(NULL) {}
	
};

struct CubeShape : PrimitiveShape
{
	glm::vec3 size;

	CubeShape(RigidBody *_body) : PrimitiveShape(_body) {size = glm::vec3(1.0f, 1.0f, 1.0f);}
	CubeShape() : PrimitiveShape() {size = glm::vec3(1.0f, 1.0f, 1.0f);}
};