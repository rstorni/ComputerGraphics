#include "shader.h"
#include <GLFW/glfw3.h>
#include <cmath>

int main()
{	
	//initialize & create window	
	if(!glfwInit())
	{
		std::cout << "FAILED TO INITIALIZE GLFW" << std::endl;
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);	
	GLFWwindow* window  = glfwCreateWindow(600, 600, "openGL Window", NULL, NULL);
	if(window == NULL)
	{
		std::cout << "FAILED TO CREATE GLFW WINDOW" << std::endl;
		exit(EXIT_FAILURE);
	}	
	glfwMakeContextCurrent(window);
	
	//initialize GLAD
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "FAILED TO INITIALIZE GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	//create Shaders	
	Shader shaderProgram();
		
	//Rendering Loop	
	while(!glfwWindowShouldClose(window))
	{
	
	}
}
