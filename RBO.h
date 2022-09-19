#ifndef RBO_CLASS_H
#define RBO_CLASS_H
#include <glad/glad.h>
class RBO
{
public:
	unsigned int ID;
	RBO();
	void Bind();
	void RBOstorage(GLsizei Width, GLsizei Height);
	void RenderBufferToFrameBuffer();
};
#endif // !RBO_CLASS_H

