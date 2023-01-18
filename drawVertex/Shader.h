#include <GLAD/glad.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

class shader
{
	public:
	shader(std::string ShaderPath);
	~shader();

	void shader::use();
	 
};
