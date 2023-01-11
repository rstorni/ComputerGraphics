#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:

	//The Program ID
	unsigned int ID;
	
	//Constructor reads and builds the shaders
	Shader(const char* vertexPath, const char* fragmentPath);
	
	//Activate the shader
	void use();

	//utility uniform functions
		
	
}

#endif
