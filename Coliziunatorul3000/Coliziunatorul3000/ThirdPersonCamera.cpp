#include <GL\glm\gtc\matrix_transform.hpp>
#include <GL\glm\gtc\constants.hpp>
#include "ThirdPersonCamera.h"

glm::mat4 ThirdPersonCamera::GetViewMatrix()
{
	glm::vec3 direction = glm::vec3(cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw));
	glm::vec3 right = glm::vec3(sin(yaw - glm::pi<float>()), 0.f, cos(yaw - glm::pi<float>()));
	glm::vec3 up = glm::cross(right, direction);
	return glm::lookAt(target + direction * zoom, target, up);
}