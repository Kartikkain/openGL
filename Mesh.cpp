#include "Mesh.h"

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indicies, std::vector <Texture>& textures)
{
	Mesh::vertices = vertices;
	Mesh::indicies = indicies;
	Mesh::textures = textures;
	Mesh::instancenum = instancenum;

	
	VBO vbo;
	IBO ibo;

	vao.Bind();
	vbo.Bind();
	ibo.Bind();

	vbo.BufferData(vertices);
	ibo.BufferData(indicies);
	vao.ConfigureAndEnableVertexArray(0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao.ConfigureAndEnableVertexArray(1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	vao.ConfigureAndEnableVertexArray(2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	vao.ConfigureAndEnableVertexArray(3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));

	vao.UnBind();
	vbo.Unbind();
	ibo.Unbind();
}

void Mesh::BindingTextures(Shader& shader)
{
	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0;i < textures.size();i++)
	{
		std::string num;
		std::string type = textures[i].type;

		if (type == "diffuse")
		{
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular")
		{
			num = std::to_string(numSpecular++);
		}
		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}
}

void Mesh::Draw(Shader& shader,Camera& camera)
{
	shader.Activate();
	vao.Bind();

	camera.matrix(shader, "camMatrix");

	for (unsigned int i = 0;i < textures.size();i++) 
	{
		textures[i].Unbind();
	}


	glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
}
