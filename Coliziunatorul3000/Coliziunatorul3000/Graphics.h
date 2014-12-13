#include<GL\glew\glew.h>
#include<GL\GLFW\glfw3.h>

#include<string>

class Graphics
{
private:
	GLFWwindow* window;
public:
	void Init(int, int, std::string);
	void Shutdown();
	GLFWwindow* GetWindow(){return window;}
};