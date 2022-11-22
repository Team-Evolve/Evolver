#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb-image/stb_image_write.h>
#include "../include/Debug.h"
#include <iostream>
#include <functional>

namespace evolver
{
	class Window
	{
	public:
		Window() = default;
		Window(int width, int height, int major = 4, int minor = 6, std::string windowName = "Evolver - Renderer");
		~Window();

		void ScreenShot(std::string name);
		void Swap();
		void PollEvents();
		void Cleanup();
		bool Loop();

#if _DEBUG
		void GetDetails();
#endif

		GLFWwindow* GetWindowPointer();
		void SetWindowPointer(GLFWwindow*);

		void SetKeyboardCallback(GLFWkeyfun callback);

	private:
		void SetWindowAtCenter();

	private:
		GLFWwindow* window;
	};
}
