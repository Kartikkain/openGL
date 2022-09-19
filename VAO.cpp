#include "VAO.h"


VAO::VAO()
{
	glGenVertexArrays(1, &ID);
}

void VAO::ConfigureAndEnableVertexArray(GLuint layoutindex,GLint numcomponents, GLenum type,GLsizei stride,void* offset)
{
	glVertexAttribPointer(layoutindex, numcomponents, type, GL_FALSE, stride, offset);

	//Enable the vertex array so opengl know how to use it
	glEnableVertexAttribArray(layoutindex);
}


void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::UnBind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}