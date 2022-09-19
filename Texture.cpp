#include "Texture.h"
#include<iostream>

Texture::Texture(const char* filepath, const char* Textype, GLuint slot, GLenum format, GLenum pixeltype)
{
	type = Textype;
	int m_Width, m_height, color_ch;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(filepath, &m_Width, &m_height, &color_ch, 0);
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	unit = slot;
	glActiveTexture(GL_TEXTURE0 + slot);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_height, 0, format, pixeltype, bytes);

	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(bytes);

}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.Activate();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void Texture::Bind() 
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
