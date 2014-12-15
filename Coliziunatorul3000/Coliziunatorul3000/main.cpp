#include <iostream>
#include <GL\glm\gtc\matrix_transform.hpp>
#include <GL\glm\gtx\transform.hpp>

#include "Graphics.h"
#include "ThirdPersonCamera.h"
#include "RigidBody.h"

#define MOUSE_SPEED (0.01f)

Graphics* graphics = NULL;
Camera* camera = NULL;

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->Zoom(-(float)yoffset);
}

void CheckCameraInputs(GLFWwindow* window)
{
	int halfWidth, halfHeight;
    glfwGetFramebufferSize(window, &halfWidth, &halfHeight);
	halfWidth /= 2;
	halfHeight /= 2;

	double xpos = 0, ypos = 0;

	glfwGetCursorPos(window, &xpos, &ypos);

	camera->RotateYaw  (((float)xpos - halfWidth)  * MOUSE_SPEED);
	camera->RotatePitch(((float)ypos - halfHeight) * MOUSE_SPEED);

	glfwSetCursorPos(window, halfWidth, halfHeight);
}

int main()
{
	graphics = new Graphics();
	graphics->Init(640, 480, "Coliziunatorul3000");
	
	std::cout<<glGetString(GL_VERSION)<<std::endl;

	graphics->LoadShaders("basicVS.vertexshader", "basicPS.pixelshader");

    int width, height;
    glfwGetFramebufferSize(graphics->GetWindow(), &width, &height);

	glfwSetInputMode(graphics->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPos(graphics->GetWindow(), width / 2, height / 2);

	glfwSetScrollCallback(graphics->GetWindow(), ScrollCallback);

	camera = new ThirdPersonCamera(0.f, glm::pi<float>(), glm::zero<glm::vec3>());

	glm::mat4 perspectiveMatrix = glm::perspective(45.f, 640.f / 480.f, 1.0f, 200.0f);
	glm::mat4 viewMatrix;
	
	graphics->SetPerspective(perspectiveMatrix);

	RigidBody *body = new RigidBody();
	body->AddForceAtBodyPoint(glm::vec3(20.f,20.f,20.f), glm::vec3(-0.5f, 0.5f, 0.5f));
	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		
		CheckCameraInputs(graphics->GetWindow());
		glDisable(GL_CULL_FACE);
		graphics->SetView(camera->GetViewMatrix());
		body->Integrate(1 / 30.f);
		graphics->DrawCube(body->GetTransformMatrix());

		glfwSwapBuffers(graphics->GetWindow());	
        glfwPollEvents();
		glGetError();
	}
	while( !glfwGetKey(graphics->GetWindow(), GLFW_KEY_ESCAPE ));

	graphics->Shutdown();
}