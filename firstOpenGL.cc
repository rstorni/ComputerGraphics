#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void init(GLFWwindow* window){};

void display(GLFWwindow* window, double currentTime)
{
	

}

int main(void)
{
	if(!glfwInit()){exit(EXIT_FAILURE);}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);


	GLFWwindow* window = glfwCreateWindow(800, 600, "Lab3", NULL, NULL);
	if (window == NULL)
	{
    	cout << "Failed to create GLFW window" << endl;
    	glfwTerminate();
    	return -1;
	}

	glfwMakeContextCurrent( window );

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
    	std::cout << "Failed to initialize GLAD" << std::endl;
    	return -1;
	}

	glfwSwapInterval(1);
	
	init(window);
	
	//animation loop
	while(!glfwWindowShouldClose(window))
	{
	//	display(window, glfwGetTime());
	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	}
	
	//glfwDestroyWindow(window);
	//glfwTerminate();
	exit(EXIT_SUCCESS);
}
