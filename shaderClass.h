#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<cerrno>
#include<glad/glad.h>


std::string get_file_content(const char* filename);

class Shader
{
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragementFile);

	void Activate();
	void Delete();

};

#endif 

