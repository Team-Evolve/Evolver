#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace evolver
{
	class Camera
	{
	public:
		Camera(int width, int height,
			glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f),
			float fov = 45.0f);

		void MouseInput(double xpos, double ypos);
		void ScrollInput(double xoffset, double yoffset);

		inline glm::mat4 GetViewMatrix();

	private:
		bool firstMouse;
		glm::vec3 cameraPos;
		glm::vec3 cameraFront;
		glm::vec3 cameraUp;
		float yaw;
		float pitch;
		float lastX, lastY;
		float fov;
		int width, height;
	};
}
