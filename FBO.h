#ifndef FBO_CLASS_H
#define FBO_CLASS_H
#include<glad/glad.h>
class FBO
{
public :
	unsigned int ID;
	FBO();
	void Bind();
	void Unbind();
	void Delete();
};
#endif // !FBO_CLASS_H

