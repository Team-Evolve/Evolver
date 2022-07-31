#include "../include/Camera.h"

namespace evolver
{
	Camera::Camera(int width, int height, glm::vec3 cameraPos, float fov)
	{
		firstMouse = true;
		yaw = -90.0f;
		pitch = 0.0f;
		lastX = width / 2;
		lastY = height / 2;
		this->fov = fov;
		this->cameraPos = cameraPos;
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	void Camera::MouseInput(double xpos, double ypos)
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		lastX = xpos; lastY = ypos;

		const float sensivity = 0.1f;
		xoffset *= sensivity;
		yoffset *= sensivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(direction);
	}

	void Camera::ScrollInput(double xoffset, double yoffset)
	{
		fov -= (float)yoffset;

		if (fov < 1.0f)
			fov = 1.0f;

		if (fov > 45.0f)
			fov = 45.0f;
	}

	glm::mat4 Camera::GetViewMatrix()
	{
		return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}
}