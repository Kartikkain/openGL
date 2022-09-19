#include "RBO.h"

RBO::RBO()
{
	glGenRenderbuffers(1, &ID);
}

void RBO::Bind()
{
	glBindRenderbuffer(GL_RENDERBUFFER, ID);
}

void RBO::RBOstorage(GLsizei Width, GLsizei Height)
{
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Width, Height);
}

void RBO::RenderBufferToFrameBuffer()
{
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, ID);
}