//#include "Skybox.h"
//
//Skybox::Skybox(float* skyboxvertices, unsigned int* skyboxindices)
//{
//
//	glGenVertexArrays(1, &skyboxVAO);
//	glGenBuffers(1, &skyboxVBO);
//	glGenBuffers(1, &skyboxIBO);
//	glBindVertexArray(skyboxVAO);
//	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxvertices), &skyboxvertices, GL_STATIC_DRAW);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxIBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxindices), &skyboxindices, GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//}
//
//void Skybox::Assingntexture()
//{
//	std::string facesofcube[6] =
//	{
//		"res/skybox/sky/right.png",
//		"res/skybox/sky/left.png",
//		"res/skybox/sky/top.png",
//		"res/skybox/sky/bottom.png",
//		"res/skybox/sky/front.png",
//		"res/skybox/sky/back.png"
//	};
//
//	glGenTextures(1, &cubemaptexture);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemaptexture);
//
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//
//
//	for (unsigned int i = 0;i < 6;i++)
//	{
//		int width, height, color_ch;
//		unsigned char* data = stbi_load(facesofcube[i].c_str(), &width, &height, &color_ch, 0);
//		if (data)
//		{
//			stbi_set_flip_vertically_on_load(false);
//
//			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//			stbi_image_free(data);
//		}
//		else
//		{
//			std::cout << "fail to load texture" << facesofcube[i] << std::endl;
//			stbi_image_free(data);
//		}
//	}
//}
//
//void Skybox::Draw(Shader& shader, Camera& camera, GLint skyboxviewloc, GLint skyboxprojectionloc)
//{
//	glDepthFunc(GL_LEQUAL);
//
//	shader.Activate();
//	glm::mat4 view = glm::mat4(1.0f);
//	glm::mat4 projection = glm::mat4(1.0f);
//
//	view = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.orientation, camera.up)));
//	projection = glm::perspective(glm::radians(45.0f), (float)camera.widht / camera.heigth, 0.1f, 100.0f);
//
//	glUniformMatrix4fv(skyboxviewloc, 1, GL_FALSE, glm::value_ptr(view));
//	glUniformMatrix4fv(skyboxprojectionloc, 1, GL_FALSE, glm::value_ptr(projection));
//
//	glBindVertexArray(skyboxVAO);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemaptexture);
//	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);
//
//
//	glDepthFunc(GL_LESS);
//}
//
//
//
//
