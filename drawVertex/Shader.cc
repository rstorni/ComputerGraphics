#include "Shader.h"

Shader(const char* vertexPath, const char* fragmentPath)
{
	/*
		Step 1 read in shaderSource code from a file
		General Idea:
		Create string, file, and stream objects
		open the file and load its buffer into a stream
		convert the stream into an std::string then convert the 
		std::string into a c_style string
	*/

	//string objects to store the GLSL code from files
	std::string vertexCode;
	std::string fragmentCode;
	
	//ifstream objects for the files containing shader source code
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	//ensure ifstream objects can throw exeptions
	vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	
	try
	{
		//open the files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		//creates string stream objects for the v and f shaders
		std::stringstream vShaderStream, fShaderStream;
		
		//read the files buffer into the streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		
		//now that we have read the files into the streams we close the files
		vShaderFile.close();
		fShaderFile.close();
	
		//convert the stream into a string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	
	//converts an std::string into a c_style string
	const char* vShaderCode = vertexCode.c_str();
	const char* fshaderCode = fragmentCode.c_str();
	

	/*
		STEP 2: Compile the shaders
	*/

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];
	
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(GL_VERTEX_SHADER, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		std:cout << "ERROR::SHADER::VERTEX::COMILATION_FAILED\n" << std::endl;
	}
	
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(GL_FRAGMENT_SHADER, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << std::endl;
	}
	
	/*
		STEP 3: create the shader program 
	*/
	
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}	
	
	glDeleteShader(vertex);
	glDeleteShader(fragment);	
}

void use()
{
	glUseProgram(ID);
}

void setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void setFloat(const std::string &name, float value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
