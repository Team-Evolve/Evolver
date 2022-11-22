#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace evolver
{
	class Transform
	{
	public:
		Transform();
		~Transform() = default;

		void Translate(glm::vec3 position);
		void Translate(float* position);
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
