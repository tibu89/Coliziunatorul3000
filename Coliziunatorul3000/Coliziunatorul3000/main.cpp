#include <iostream>
#include <GL\glm\gtc\matrix_transform.hpp>
#include <GL\glm\gtx\transform.hpp>

#include "Graphics.h"
#include "PhysicsEngine.h"
#include "FirstPersonCamera.h"
#include "ThirdPersonCamera.h"

#define MOUSE_SPEED (0.002f)
#define TRANSLATE_SPEED (0.02f)

Graphics* graphics = NULL;
Camera* camera = NULL;

glm::vec3 cameraDirectionVector;

PhysicsEngine* physics;

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera->Zoom(-(float)yoffset);
}

void KeyCallback(GLFWwindow* window, int button, int scancode, int action, int mods)
{
	float sign = 0.f;

	switch(action)
	{
	case GLFW_PRESS:
		sign = 1.f;
		break;
	case GLFW_RELEASE:
		sign = -1.f;
		break;
	default:
		return;
	}

	switch(button)
	{
	case 'w':
	case 'W':
		cameraDirectionVector += sign * glm::vec3(  0.f,  0.f, -1.f );
		break;
	case 's':
	case 'S':
		cameraDirectionVector += sign * glm::vec3(  0.f,  0.f,  1.f );
		break;
	case 'a':
	case 'A':
		cameraDirectionVector += sign * glm::vec3( -1.f,  0.f,  0.f );
		break;
	case 'd':
	case 'D':
		cameraDirectionVector += sign * glm::vec3(  1.f,  0.f,  0.f );
		break;
	}
}

void CheckCameraInputs(GLFWwindow* window)
{
	int halfWidth, halfHeight;
    glfwGetFramebufferSize(window, &halfWidth, &halfHeight);
	halfWidth /= 2;
	halfHeight /= 2;

	double xpos = 0, ypos = 0;

	glfwGetCursorPos(window, &xpos, &ypos);

	if( glfwGetMouseButton( window, GLFW_MOUSE_BUTTON_MIDDLE ) == GLFW_PRESS )
	{
		camera->Translate( glm::vec3( 0.f, (halfHeight - (float)ypos) * TRANSLATE_SPEED, 0.f ) );
	}
	else
	{
		camera->RotateYaw  ((halfWidth  - (float)xpos) * MOUSE_SPEED);
		camera->RotatePitch((halfHeight - (float)ypos) * MOUSE_SPEED);
	}

	glfwSetCursorPos(window, halfWidth, halfHeight);

	camera->Translate( cameraDirectionVector * TRANSLATE_SPEED );
}

int main()
{
	//ContactGenerator contactGenerator(1000);
	graphics = new Graphics();
	graphics->Init(640, 480, "Coliziunatorul3000");

	physics = new PhysicsEngine();
	
	std::cout<<glGetString(GL_VERSION)<<std::endl;
	
    int width, height;
    glfwGetFramebufferSize(graphics->GetWindow(), &width, &height);

	glfwSetInputMode(graphics->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetCursorPos(graphics->GetWindow(), width / 2, height / 2);

	glfwSetScrollCallback(graphics->GetWindow(), ScrollCallback);
	glfwSetKeyCallback(graphics->GetWindow(), KeyCallback);

	camera = new FirstPersonCamera(0.f, glm::pi<float>(), glm::vec3(0.f, 0.f,5.f));

	glm::mat4 perspectiveMatrix = glm::perspective(45.f, 640.f / 480.f, 1.0f, 200.0f);
	glm::mat4 viewMatrix;

	glm::mat4 planeModelMatrix = glm::translate(glm::vec3(0.0f, -10.0f, 0.0f)) * glm::scale(glm::vec3(100.0f, 100.0f, 100.0f));

	physics->AddPlane(glm::vec3(0.f, 1.f, 0.f), -10.f);
	RigidBodyID id1 = physics->AddCube();
	
	graphics->SetPerspective(perspectiveMatrix);
	
	physics->GetRigidBodyByID(id1).AddForceAtBodyPoint(glm::vec3(1.f,-4.f,1.f), glm::vec3(-0.5f, 0.5f, 0.5f));

	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		CheckCameraInputs(graphics->GetWindow());

		glDisable(GL_CULL_FACE);
		graphics->SetView(camera->GetViewMatrix());
		//body->Integrate(1 / 30.f);
		graphics->DrawCube(physics->GetRigidBodyByID(id1).GetTransformMatrix());

		graphics->DrawPlane(planeModelMatrix);

		physics->Update(1 / 30.f);
		physics->DebugContacts(graphics);

		glfwSwapBuffers(graphics->GetWindow());	
        glfwPollEvents();
		glGetError();
	}
	while( !glfwGetKey(graphics->GetWindow(), GLFW_KEY_ESCAPE ));

	graphics->Shutdown();
}