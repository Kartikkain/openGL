#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include "shaderClass.h"

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameramatrix = glm::mat4(1.0f);

	bool firstClick = true;

	int widht,heigth;

	float speed = 0.01f;
	float sensetivity = 100.0f;

	Camera(int widht, int heigth, glm::vec3 position);

	void updatematrix(float FOVdegree, float nearplane, float farplane);
	void matrix(Shader& shader, const char* uniform);
	void input(GLFWwindow* window);

};
#endif