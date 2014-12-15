#pragma once

#include<GL\glew\glew.h>
#include<GL\GLFW\glfw3.h>
#include<GL\glm\glm.hpp>

#include<string>

class Graphics
{
private:
	GLFWwindow* window;
	GLuint programID;
	GLuint vertexArrayID;

	glm::mat4 perspectiveMatrix;
	glm::mat4 viewMatrix;

	GLuint projectionMatrixID;
	GLuint viewMatrixID;
	GLuint modelMatrixID;

	GLuint cubeVertexBuffer;
	GLuint cubeNormalBuffer;

	static const GLfloat cubeVertexData[];
	static const GLfloat cubeNormalData[];

	void InitCubeModel(); //lol, model

public:
	void Init(int, int, std::string);
	void Shutdown();
	GLFWwindow* GetWindow(){return window;}

	void LoadShaders(std::string vsPath, std::string psPath);
	void SetPerspective(glm::mat4 const &P)
	{
		perspectiveMatrix = P;
		glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &perspectiveMatrix[0][0]);
	}
	void SetView(glm::mat4 const &V)
	{
		viewMatrix = V;
		glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);
	}

	void DrawCube(glm::mat4 const &modelMatrix);
};