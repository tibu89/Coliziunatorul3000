#include<GL\glm\glm.hpp>

class Camera
{
protected:
	float pitch, yaw;
	float zoom;

public:
	Camera(float _pitch, float _yaw) {pitch = _pitch; yaw = _yaw;}
	Camera() {pitch = 0.f; yaw = 0.f;}

	virtual glm::mat4 GetViewMatrix() = 0;

	virtual void Translate(glm::vec3 offset) = 0;
	virtual void RotatePitch(float rads) = 0;
	virtual void RotateYaw(float rads) = 0;
	virtual void Zoom(float amount) = 0;
};