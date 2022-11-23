#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace evolver
{
	class Transform
	{
	public:
		struct ModelMatrixVariables
		{
			ModelMatrixVariables()
			{
				position = glm::vec3(0.0f, 0.0f, 0.0f);
				for (int i = 0; i < 3; i++)
				{
					rotations[i] = glm::vec3(0.0f, 0.0f, 0.0f);
					angles[i] = 0.0f;
					scales[i] = glm::vec3(1.0f, 1.0f, 1.0f);
				}
			}

			glm::vec3 position;
			glm::vec3 rotations[3];
			float angles[3];
			glm::vec3 scales[3];
		};

	public:
		Transform();
		~Transform() = default;

		void CalculateModelMatrix(ModelMatrixVariables& variables);
		
		void SetProjMatrix(float fov, float aspect, float near, float far);
		
		inline void SetViewMatrix(glm::mat4 view) { viewMatrix = view; }
		inline glm::mat4 GetModelMatrix() const { return modelMatrix; }
		inline glm::mat4 GetViewMatrix() const { return viewMatrix; }
		inline glm::mat4 GetProjMatrix() const { return projMatrix; }
		inline glm::mat4 GetMVMatrix() const { return (viewMatrix * modelMatrix); }
		inline glm::mat4 GetMVPMatrix() const { return (projMatrix * viewMatrix * modelMatrix); }

	private:
		glm::mat4 modelMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 projMatrix;
	};
}
