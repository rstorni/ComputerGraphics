#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

float verticies[] = {
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f
};

unsigned int indicies[] = {
	0, 1, 3,
	1, 2, 3
};

bool didShaderCompile(unsigned int shader)
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

unsigned int createShaderProgram()
{
	/*
		creates Vertex and Fragmentation Shader
		the strings are GLSL the actual shader code	
	*/
	const char* vshaderSource = 
		"#version 410 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main(void)\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fshaderSource = 
		"#version 410 core\n"
		"out vec4 FragColor;\n"
		"void main(void)\n"
		"{\n"
		"	FragColor = vec4(4.0f, 1.0f, 0.2f, 1.0f);\n"
		"}\0";
	
	//creates the vertex shader object
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);	
	
	//attatch the vector shader source code to the vertex shader object and compile
	glShaderSource(vertexShader, 1, &vshaderSource, NULL);
	glCompileShader(vertexShader);
	if(!didShaderCompile(vertexShader))
	{
		std::cout << "Vertex Shader Failed to compile" << std::endl;
		exit(EXIT_FAILURE);
	}		
	
	//creates the fragment shader object	
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	//attatch the fragment shader source to the fragment shader object and compile
	glShaderSource(fragmentShader, 1, &fshaderSource, NULL);
	glCompileShader(fragmentShader);
	if(!didShaderCompile(fragmentShader))
	{
		std::cout << "Fragment Shader Failed to Compile" << std::endl;
		exit(EXIT_FAILURE);
	}	
	
	//creating the shader program
	unsigned int shaderProgram;
	
	// the glCreateProgram function returns the ID reference to the program.
	shaderProgram = glCreateProgram();
				
	//attatch the shaders to the shader program and then link them
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	//Delete the fragment and vertex shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);	
	return shaderProgram;		
}

void init(GLFWwindow* window)
{
	/*
		creates the verext array object aand then binds it
		After creating this any VBO and vertexAttribPointer will
		be bound to the VAO.
	*/
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	/*
		Creating the VBO wich will allow us to pass vertex data to the
		GPU. Vertex buffer will be of type ARRAY_BUFFER
	*/	
	unsigned int VBO;
	glGenBuffers(1, &VBO);	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	/*
		discribes to the gpu how the vertex attributes are layed out in the VBO.
		Because we use a VAO this step also links the glVertexAttribPointer to the VBO 
		and all of that is stored in the VAO.	
	*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	/*
		create a Element Buffer Object that will allow us to tell the GPU to
		repeatedly draw specified vertexes.

		This is helpfull as it lets us draw more complex shapes with out having to 
		repeat vertex declarations.
	*/			
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	//bind the created buffer to the GL_ELEMENT_ARRAY_BUFFER type;	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	
	//Input data into the GL_ELEMENT_ARRAY_BUFFER
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
		

	unsigned int shader = createShaderProgram();
	glUseProgram(shader);
}

void display(GLFWwindow* window, double currentTime)
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);	
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(void)
{
	//Initialize the glfw library
	if(!glfwInit())
	{
		std::cout << "glfw failed to initialize \n";
		exit(EXIT_FAILURE);
	}

	//Setting up the context for openGL	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	//Creates a GLFW window	
	GLFWwindow* window = glfwCreateWindow(600, 600, "drawing a vertex", NULL, NULL);
	if(window == NULL)
	{
		std::cout << "window failed to create \n";
		exit(EXIT_FAILURE);
	}
		
	//Creates the context	
	glfwMakeContextCurrent(window);
	
	//Resets the glViewport if the window resizes	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);	
	
	//initialize glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "glad failed to initialize \n";
		exit(EXIT_FAILURE);	
	}

	init(window);			
			
	//The rendering loop	
	while(!glfwWindowShouldClose(window))
	{
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		
		//checks to see if anyone wants to close the window
		glfwPollEvents();
	}
	//terminate everything
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
	
}
