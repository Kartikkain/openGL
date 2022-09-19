#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include "VBO.h"

class VAO
{
public:
	GLuint ID;
	VAO();
	void ConfigureAndEnableVertexArray(GLuint layoutindex,GLint numcomponents,GLenum type,GLsizei stride,void*offset);
	void Bind();
	void UnBind();
	void Delete();

};

#endif 
