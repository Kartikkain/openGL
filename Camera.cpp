#include "Camera.h"
#include<iostream>
using namespace std;
Camera::Camera(int widht, int heigth, glm::vec3 position)
{
	Camera::widht = widht;
	Camera::heigth = heigth;
	Position = position;
}

void Camera::updatematrix(float FOVdegree, float nearplane, float farplane)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + orientation, up);
	projection = glm::perspective(glm::radians(FOVdegree),(float)widht/heigth,nearplane,farplane);

	cameramatrix = projection * view;
}

void Camera::matrix(Shader& shader, const char* uniform)
{
	GLint cam_loc = glGetUniformLocation(shader.ID, uniform);
	glUniformMatrix4fv(cam_loc, 1, GL_FALSE, glm::value_ptr(cameramatrix));
}

void Camera::input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * orientation;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -orientation;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(orientation, up));
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(orientation, up));
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		Position += speed * up;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		Position += speed * -up;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		speed = 0.4f;
	}
	else if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
	{
		speed = 0.01f;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (firstClick)
		{
			glfwSetCursorPos(window, (widht / 2), (heigth / 2));
			firstClick = false;
		}

		double mousex;
		double mousey;

		glfwGetCursorPos(window, &mousex, &mousey);

		float rotx = sensetivity * (float)(mousey - (heigth / 2)) / heigth;
		float roty = sensetivity * (float)(mousex - (heigth / 2)) / widht;

		glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotx), glm::normalize(glm::cross(orientation, up)));
		
		if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			orientation = newOrientation;
		}

		orientation = glm::rotate(orientation, glm::radians(-roty), up);
		glfwSetCursorPos(window, (widht / 2), (heigth / 2));
	}

	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = false;
	}
}