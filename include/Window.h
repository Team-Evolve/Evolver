#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image_write.h>

#include <iostream>

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
		inline bool Loop();

		#if _DEBUG
		void GetDetails();
		#endif

		GLFWwindow* GetWindowPointer();
		void SetWindowPointer(GLFWwindow*);

		void SetWindowAtCenter();
		inline GLFWwindow* GetWindowPointer();
		inline void SetWindowPointer(GLFWwindow*);

	private:
		GLFWwindow* window;
