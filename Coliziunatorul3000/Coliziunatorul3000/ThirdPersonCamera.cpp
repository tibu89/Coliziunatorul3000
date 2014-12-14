#include <GL\glm\gtc\matrix_transform.hpp>
#include <GL\glm\gtc\constants.hpp>
#include "ThirdPersonCamera.h"

glm::mat4 ThirdPersonCamera::GetViewMatrix()
{
	glm::vec3 direction = glm::vec3(cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw));
	glm::vec3 right = glm::vec3(sin(yaw - glm::half_pi<float>()), 0.f, cos(yaw - glm::half_pi<float>()));
	glm::vec3 up = glm::cross(right, direction);
	return glm::lookAt(target - direction * zoom, target, up);
}

void ThirdPersonCamera::Translate(glm::vec3 offset)
{
	target += offset;
}
	
void ThirdPersonCamera::RotatePitch(float rads)
{
	pitch += rads;
	if(pitch >= glm::half_pi<float>())
	{
		pitch = glm::half_pi<float>();
	}
	else if(pitch <= -glm::half_pi<float>())
	{
		pitch = -glm::half_pi<float>();
	}
}

void ThirdPersonCamera::RotateYaw(float rads)
{
	yaw += rads;

	if(yaw >= 2 * glm::pi<float>())
	{
		yaw -= 2 * glm::pi<float>();
	}
	else if(yaw < 0)
	{
		yaw += 2 * glm::pi<float>();
	}
}

void ThirdPersonCamera::Zoom(float amount)
{
	zoom += amount;
	if(zoom < 3.0f)
		zoom = 3.0f;
}