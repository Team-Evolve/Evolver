#include "../include/Window.h"

namespace evolver
{
	Window::Window(int width, int height, int major, int minor, std::string windowName)
	{
		if (!glfwInit()) exit(EXIT_FAILURE);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);

#if defined(__APPLE__)
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

		if (window == nullptr)
		{
			std::cout << "::Window:: Window Pointer Cannot Initialized\n";
			return;
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) exit(EXIT_FAILURE);
	}

	Window::~Window()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Window::ScreenShot(std::string name)
	{
		stbi_flip_vertically_on_write(true);

		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		uint8_t* ptr = (uint8_t*)malloc(width * height * 4);

		glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, ptr);
		stbi_write_png(name.c_str(), width, height, 4, ptr, 0);

		std::cout << "Saved " + name << "\n";

		free(ptr);
	}

	bool Window::Loop()
	{
		return (!glfwWindowShouldClose(window));
	}

	void Window::Swap()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void Window::Cleanup()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	GLFWwindow* Window::GetWindowPointer()
	{
		return window;
	}

	void Window::SetWindowPointer(GLFWwindow* window)
	{
		this->window = window;
	}

#if _DEBUG
	void Window::GetDetails()
	{
		const GLubyte* renderer = glGetString(GL_RENDERER);
		const GLubyte* vendor = glGetString(GL_VENDOR);
		const GLubyte* version = glGetString(GL_VERSION);
		const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

		GLint major, minor;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);
		printf("GL Vendor : %s\n", vendor);
		printf("GL Renderer : %s\n", renderer);
		printf("GL Version (string) : %s\n", version);
		printf("GL Version (integer) : %d.%d\n", major, minor);
		printf("GLSL Version : %s\n", glslVersion);

		std::cout << "Extensions: " << std::endl;

		GLint nExtensions;
		glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);

		for (int i = 0; i < nExtensions; i++)
			printf("%s\n", glGetStringi(GL_EXTENSIONS, i));
	}
#endif
}