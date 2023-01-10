#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

float verticies[] = {
	0.0, 0.0, 0.0,
	0,5, 0.0, 0.0,
	0.0, 0.5, 0.0,
	-0.5, -0.5, 0.0,
	-0.5, 0.0, 0.0,
	0.0, -0.5, 0.0
};
	
bool shaderCompiled(unsigned int shader)
{
	int success = 0;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	
	if(!success)
	{
		return false;
	}
	return true;
}

bool programLinked(unsigned int program)
{
	int success = 0;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	
	if(!success)
	{
		return false;
	}
	return true;
}

void initialize()
{
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);	
	glBindVertexArray(VAO);
	
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

unsigned int createShaderProgram()
{
	const char* vSource = 
	"#version 410 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main(void)\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

	const char* fSource = 
	"#version 410 core\n"
	"out vec4 FragColor;\n"
	"void main(void)\n"
	"{\n"
	"	FragColor = vec4(0.3f, 0.6f, 0.9f, 0.7f);\n"
	"}\0";
	
	unsigned int vShader;
	vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vSource, NULL);
	glCompileShader(vShader);
	if(!shaderCompiled(vShader))
	{
		std::cout << "VERTEX SHADER FAILED TO COMPILE" <<std::endl;
		exit(EXIT_FAILURE);
	}
	
	unsigned int fShader;
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fSource, NULL);
	glCompileShader(fShader);
	if(!shaderCompiled(fShader))
	{
		std::cout << "FRAGMENT SHADER FAILED TO COMPILE" << std::endl;
		exit(EXIT_FAILURE);
	}	
	
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);
	glLinkProgram(shaderProgram);
	if(!programLinked(shaderProgram))
	{
		std::cout << "SHADER PROGRAM FAILED TO LINK" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	glDeleteShader(vShader);
	glDeleteShader(fShader);
	
	return shaderProgram;	
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	unsigned int shader;
	if(!glfwInit())
	{
		std::cout << "FAILED TO INITIALIZE GLFW" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	
	GLFWwindow* window = glfwCreateWindow(600, 600, "drawing two triangles", NULL, NULL);
	if(window == NULL)
	{
		std::cout << "WINDOW CREATION FAILED" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	glfwMakeContextCurrent(window);	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "FAILED TO INITIALIZE GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	initialize();
	shader = createShaderProgram();	
	glUseProgram(shader);
	while(!glfwWindowShouldClose(window))
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);	

}
