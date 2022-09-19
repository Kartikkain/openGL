#ifndef VBO_CLASS_H
#define VBO_CLASS_H
#include<glm/glm.hpp>
#include<glad/glad.h>
#include<vector>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

struct Offset
{
	glm::vec3 offset;
};

class VBO
{
public:
	GLuint ID;
	VBO();
	void BufferData(std::vector<Vertex>& verticies);
	void BufferData(std::vector<float>& skyboxvertices);
	void Bind();
	void Unbind();
	void Delete();

};

#endif 

