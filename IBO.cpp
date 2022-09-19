#include "IBO.h"

IBO::IBO()
{
	glGenBuffers(1, &ID);
}

void IBO::BufferData(std::vector<GLuint>& indicies)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(GLuint), indicies.data(), GL_STATIC_DRAW);
}
void IBO::Bind()
{
	//Binding the IBO specifying its GL_ELEMENT_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void IBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IBO::Delete()
{
	glDeleteBuffers(1, &ID);
}