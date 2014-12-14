#include "Camera.h"

class ThirdPersonCamera : public Camera
{
private:
	glm::vec3 target;
public:
	ThirdPersonCamera(float _pitch, float _yaw, glm::vec3 _target, float _zoom = 5.0f) : Camera(_pitch, _yaw){target = _target;zoom = _zoom;}

	glm::mat4 GetViewMatrix();

	void Translate(glm::vec3 offset);
	void RotatePitch(float rads);
	void RotateYaw(float rads);
	void Zoom(float amount);
};