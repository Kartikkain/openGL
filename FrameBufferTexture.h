#ifndef FBOTEXTURE_CLASS_H
#define FBOTEXTURE_CLASS_H
#include<glad/glad.h>

class FBOTexture
{
public:
	unsigned int ID;
	FBOTexture();
	void Bind();
	void Gettexture(GLsizei Width, GLsizei Height);
	void AssignTextureToFramebuffer();
};
#endif // !FBOTEXTURE_CLASS_H

