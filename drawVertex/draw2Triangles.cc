#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

float verticies[] = {
// 		Position (x,y,Z) 	Color (R,G,B)	Texture(S,T)
        -0.4f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // left 
        0.4f, -0.4f, 0.0f,	0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // right
        0.0f, 0.4f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f // top 
        // second triangle
        //0.0f, -0.5f, 0.0f,	0.5f, 0.5f, 0.2f, // left
         //0.9f, -0.5f, 0.0f, 0.6f, 0.0f, 0.5f, // right
        // 0.45f, 0.5f, 0.0f, 0.0f, 0.3f, 0.9f  // top 
};
	
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
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

unsigned int createShaderProgram()
{
	int success = 0;
	char infoLog[512];
	
	const char* vSource = 
	"#version 410 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec3 Color; \n"
	"out vec3 ourColor;\n"
	"uniform float offset;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(-aPos.x + offset, -aPos.y + offset, aPos.z, 1.0);\n"
	"	ourColor = aColor;\n"
	"}\0";

	const char* fSource = 
	"#version 410 core\n"
	"in vec3 ourColor;\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(ourColor, 1.0);\n"
	"}\0";
	
	unsigned int vShader;
	vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vSource, NULL);
	glCompileShader(vShader);
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vShader, 512, NULL, infoLog);
		std::cout << "VERTEX SHADER FAILED TO COMPILE\n" << infoLog << std::endl;
		exit(EXIT_FAILURE);
	}
	
	unsigned int fShader;
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fSource, NULL);
	glCompileShader(fShader);
	if(!success)
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
		/*
			use the time value and a sin function to 
			modulate the color value from 0 to 1
			This is done by the sin(T)/2 + .5
		*/
		//float timeValue = glfwGetTime();
	 	//float blueValue = sin(timeValue) / 2.0f + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shader, "ourColor");
		//glUniform4f(vertexColorLocation, 0.5f, blueValue, blueValue, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		float timeValue = glfwGetTime();
		float offset = sin(timeValue)/2.0f;
		unsigned int vertexOffsetLocation = glGetUniformLocation(shader, "offset");
		glUniform1f(vertexOffsetLocation, offset);	
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);	

}
