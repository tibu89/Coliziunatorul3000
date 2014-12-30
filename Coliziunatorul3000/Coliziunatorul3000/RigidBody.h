#pragma once

#define GLM_SWIZZLE
#include <GL\glm\glm.hpp>
#include <GL\glm\gtc\quaternion.hpp>
#include <GL\glm\gtx\quaternion.hpp>
#include <GL\glm\gtc\matrix_transform.hpp>
#include <GL\glm\gtx\transform.hpp>

class RigidBody
{
protected:
	glm::vec3 position;
	glm::vec3 velocity;

	glm::quat orientation;
	glm::vec3 angularVelocity;

	glm::vec3 acceleration;
	glm::vec3 lastFrameAcceleration;
	glm::vec3 torque;

	glm::vec3 forceAccum;
	glm::vec3 torqueAccum;

	float invMass;

	glm::mat3 inverseInertiaTensor;
	glm::mat3 inverseInertiaTensorWorld;
	glm::mat4 modelTransformMatrix;

	float linearDamping;
	float angularDamping;
public:

	void Integrate(float dt);
	void CalculateDerivedData();
	void ClearAccumulators();
	void AddForce(const glm::vec3 &force);
	void AddForceAtPoint(const glm::vec3 &force, const glm::vec3 &point);
	void AddForceAtBodyPoint(const glm::vec3 &force, const glm::vec3 &point);

	const glm::mat4& GetTransformMatrix(){return modelTransformMatrix;}

	const glm::vec3& GetPosition(){return position;}

	RigidBody()
	{
		invMass = 1.f;
		linearDamping = 0.99f;
		angularDamping = 0.99f;

		CalculateDerivedData();
	}
};