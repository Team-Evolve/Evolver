#include "../include/Transform.h"

namespace evolver
{
	Transform::Transform()
	{
		modelMatrix = glm::mat4(1.0f);
		viewMatrix = glm::mat4(1.0f);
		projMatrix = glm::mat4(1.0f);
	}

	void Transform::Translate(glm::vec3 position)
	{
		modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, position);
	}

	void Transform::Translate(float* position)
	{
		glm::vec3 pos(position[0], position[1], position[2]);

		modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, pos);
	}

	void Transform::SetProjMatrix(float fov, float aspect, float near, float far)
	{
		projMatrix = glm::perspective(glm::radians(fov), aspect, near, far);
	}
}