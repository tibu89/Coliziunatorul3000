#include <iostream>
#include <GL\glm\gtc\matrix_transform.hpp>
#include <GL\glm\gtx\transform.hpp>

#include "Graphics.h"
#include "ThirdPersonCamera.h"

#define MOUSE_SPEED (0.01f)

Graphics* graphics = NULL;

void CheckCameraInputs(GLFWwindow* window, Camera* camera)
{
	int halfWidth, halfHeight;
    glfwGetFramebufferSize(window, &halfWidth, &halfHeight);
	halfWidth /= 2;
	halfHeight /= 2;

	double xpos = 0, ypos = 0;

	glfwGetCursorPos(window, &xpos, &ypos);

	camera->RotateYaw  ((xpos - halfWidth)  * MOUSE_SPEED);
	camera->RotatePitch((ypos - halfHeight) * MOUSE_SPEED);

	glfwSetCursorPos(window, halfWidth, halfHeight);
}

int main()
{
	graphics = new Graphics();
	graphics->Init(640, 480, "Coliziunatorul3000");
	
    int width, height;
    glfwGetFramebufferSize(graphics->GetWindow(), &width, &height);

	glfwSetInputMode(graphics->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPos(graphics->GetWindow(), width / 2, height / 2);

	Camera* camera = new ThirdPersonCamera(0.f, glm::pi<float>(), glm::zero<glm::vec3>());

	glm::mat4 perspectiveMatrix = glm::perspective(45.f, 4.f / 3.f, 1.0f, 200.0f);
	glm::mat4 viewMatrix;

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(&perspectiveMatrix[0][0]);

	while(!glfwWindowShouldClose(graphics->GetWindow()))
	{
		CheckCameraInputs(graphics->GetWindow(), camera);

        float ratio;
        glfwGetFramebufferSize(graphics->GetWindow(), &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
		viewMatrix = camera->GetViewMatrix();
		glLoadMatrixf(&viewMatrix[0][0]);
        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-0.6f, -0.4f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(0.6f, -0.4f, 0.f);
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();
        glfwSwapBuffers(graphics->GetWindow());
        glfwPollEvents();
    }

	graphics->Shutdown();
}