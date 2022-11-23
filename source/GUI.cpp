#include "../include/GUI.h"

namespace evolver
{
	GUI::GUI(GLFWwindow* window)
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

		ImGui::StyleColorsDark();
	}

	GUI::~GUI()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void GUI::Render()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void GUI::CreateNewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void GUI::StartFrame(const char* frameName)
	{
		ImGui::Begin(frameName);
	}

	void GUI::SetSliderFloat(const char* variableName, float& variable, float minValue, float maxValue)
	{
		ImGui::SliderFloat(variableName, &variable, minValue, maxValue);
	}

	void GUI::SetSliderFloat3(const char* variableName, glm::vec3& variable, float minValue, float maxValue)
	{
		float temp[3] = { variable.x, variable.y, variable.z };

		ImGui::SliderFloat3(variableName, temp, minValue, maxValue);
	
		variable = glm::vec3(temp[0], temp[1], temp[2]);
	}

	void GUI::SetSliderFloat3(const char* variableName, float* variable, float minValue, float maxValue)
	{
		ImGui::SliderFloat3(variableName, variable, minValue, maxValue);
	}

	void GUI::SetRGB(const char* variableName, glm::vec3& variable)
	{
		float temp[3] = { variable.x, variable.y, variable.z };

		ImGui::ColorEdit3(variableName, temp);

		variable = glm::vec3(temp[0], temp[1], temp[2]);
	}

	void GUI::SetRGB(const char* variableName, float* variable)
	{
		ImGui::ColorEdit3(variableName, variable);
	}

	void GUI::SetImage(unsigned int variable, unsigned int width, unsigned int height)
	{
		ImGui::Image((void*)(intptr_t)(variable), ImVec2(width, height));
	}

	void GUI::SetText(const char* text)
	{
		ImGui::Text(text);
	}

	void GUI::EndFrame()
	{
		ImGui::End();
	}
}