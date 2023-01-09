#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

void init(GLFWwindow* window){}

void display(GLFWwindow* window, double currentTime)
{
	//sets the color of the background when we clear the screen
	glClearColor(1.0, 0.0, 0.0, 1.0);
	
	//clears the screen
	glClear(GL_COLOR_BUFFER_BIT);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(void)
{
	//initialize glfw windowing tool
	if(!glfwInit())
	{
		std::cout << "glfw failed to initialize \n";
		exit(EXIT_FAILURE);
	}
	
	//configure window context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	
	//create glfw window
	GLFWwindow* window = glfwCreateWindow(600, 600, "Rami's Window", NULL, NULL);
	if(window == NULL)
	{
		std::cout << "window failed to create \n";
		exit(EXIT_FAILURE);
	}
	
	//create context from window
	glfwMakeContextCurrent(window);
	
	//resizes openGL view port on any window resize
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	//allows for syncronization
	glfwSwapInterval(1);
	
	//initialize glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to load Glad \n";
		exit(EXIT_FAILURE);
	}
	
	//display loop
	while(!glfwWindowShouldClose(window))
	{
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();	
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
	
}
