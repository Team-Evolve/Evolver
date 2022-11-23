#pragma once

#include <glad/glad.h>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include <string>
#include <glm/glm.hpp>

namespace evolver
{
	class GUI
	{
	public:
		GUI(GLFWwindow* window);
		~GUI();

		void Render();
		void CreateNewFrame();

		void StartFrame(const char* frameName);
		void SetSliderFloat(const char* variableName, float& variable, float minValue, float maxValue);
		void SetSliderFloat3(const char* variableName, glm::vec3& variable, float minValue, float maxValue);
		void SetSliderFloat3(const char* variableName, float* variable, float minValue, float maxValue);
		void SetRGB(const char* variableName, glm::vec3& variable);
		void SetRGB(const char* variableName, float* variable);
		void SetImage(unsigned int variable, unsigned int width, unsigned int height);
		void SetText(const char* text);
		void EndFrame();
	};
}