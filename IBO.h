#ifndef IBO_CLASS_H
#define IBO_CLASS_H
#include<glad/glad.h>
#include<vector>

class IBO
{
public:
	GLuint ID;

	IBO();

	void BufferData(std::vector<GLuint>& indicies);
	void Bind();
	void Unbind();
	void Delete();

};

#endif 

