#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <string>
#include "VAO.h"
#include "VBO.h"
#include "IBO.h"
#include "Camera.h"
#include "Texture.h"

class Mesh
{ 
public:
	std::vector <Vertex> vertices;
	std::vector <GLuint> indicies;
	std::vector <Texture> textures;

	VAO vao;
	unsigned int instancenum;
	Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indicies, std::vector <Texture>& textures);
	void BindingTextures(Shader& shader);
	void Draw(Shader& shader,Camera& camera);
};

#endif 

