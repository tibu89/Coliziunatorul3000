#include "Graphics.h"

void Graphics::Init(int w, int h, std::string title)
{
	if(!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
	if(!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
}

void Graphics::Shutdown()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}