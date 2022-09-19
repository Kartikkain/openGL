#include "VBO.h"

VBO::VBO()
{
	glGenBuffers(1, &ID);
}

void VBO::BufferData(std::vector<Vertex>& verticies)
{
	glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Vertex), verticies.data(), GL_STATIC_DRAW);
	
}

void BufferData(std::vector<float>& skyboxvertices)
{
	glBufferData(GL_ARRAY_BUFFER, skyboxvertices.size() * sizeof(float), skyboxvertices.data(), GL_STATIC_DRAW);

}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	glDeleteBuffers(1, &ID);
}