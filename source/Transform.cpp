#include "../include/Transform.h"

namespace evolver
{
	Transform::Transform()
	{
		modelMatrix = glm::mat4(1.0f);
		viewMatrix = glm::mat4(1.0f);
		projMatrix = glm::mat4(1.0f);
	}

	void Transform::CalculateModelMatrix(ModelMatrixVariables& variables)
	{
		modelMatrix = glm::mat4(1.0f);

		modelMatrix = glm::translate(modelMatrix, variables.position);

		for (int i = 0; i < 3; i++)
		{
			if (variables.angles[i] == 0.0f) continue;
			modelMatrix = glm::rotate(modelMatrix, glm::radians(variables.angles[i]), variables.rotations[i]);
		}

		for (int i = 0; i < 3; i++)
		{
			modelMatrix = glm::scale(modelMatrix, variables.scales[i]);
		}
	}

	void Transform::SetProjMatrix(float fov, float aspect, float near, float far)
	{
		projMatrix = glm::perspective(glm::radians(fov), aspect, near, far);
	}
}