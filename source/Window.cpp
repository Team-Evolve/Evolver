#include "../include/Window.h"

void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
evolver::Window::Window(int width, int height, int major = 4, int minor = 6, std::string windowName = "Evolver - Renderer")
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		std::cout << "W Key Pressed\n";
	}
}

namespace evolver
{
	Window::Window(int width, int height, int major, int minor, std::string windowName) :
		window(nullptr)
	{
		if (!glfwInit()) exit(EXIT_FAILURE);
	if (!glfwInit()) exit(EXIT_FAILURE);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);

#if defined(__APPLE__)
	#if defined(__APPLE__)
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	#endif

		if(major == 4 && minor >= 5)
			#define GL_4_5_OR_NEWER

		window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

		if (window == nullptr)
		{
			std::cout << "::Window:: Window Pointer Cannot Initialized\n";
			return;
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) exit(EXIT_FAILURE);

		glfwSetKeyCallback(window, Key_Callback);
	}
	window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

	Window::~Window()
	if (window == nullptr)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		std::cout << "::Window:: Window Pointer Cannot Initialized\n";
		return;
	}

	void Window::SetWindowAtCenter()
	{
		int window_x, window_y;
		glfwGetWindowPos(window, &window_x, &window_y);

		int window_width, window_height;
		glfwGetWindowSize(window, &window_width, &window_height);

		// Halve the window size and use it to adjust the window position to the center of the window
		window_width *= 0.5;
		window_height *= 0.5;

		window_x += window_width;
		window_y += window_height;

		// Get the list of monitors
		int monitors_length;
		GLFWmonitor** monitors = glfwGetMonitors(&monitors_length);

		if (monitors == NULL) {
			// Got no monitors back
			return;
		}

		// Figure out which monitor the window is in
		GLFWmonitor* owner = NULL;
		int owner_x, owner_y, owner_width, owner_height;

		for (int i = 0; i < monitors_length; i++) {
			// Get the monitor position
			int monitor_x, monitor_y;
			glfwGetMonitorPos(monitors[i], &monitor_x, &monitor_y);

			// Get the monitor size from its video mode
			int monitor_width, monitor_height;
			GLFWvidmode* monitor_vidmode = (GLFWvidmode*)glfwGetVideoMode(monitors[i]);

			if (monitor_vidmode == NULL) {
				// Video mode is required for width and height, so skip this monitor
				continue;

			}
			else {
				monitor_width = monitor_vidmode->width;
				monitor_height = monitor_vidmode->height;
			}

			// Set the owner to this monitor if the center of the window is within its bounding box
			if ((window_x > monitor_x && window_x < (monitor_x + monitor_width)) && (window_y > monitor_y && window_y < (monitor_y + monitor_height))) {
				owner = monitors[i];

				owner_x = monitor_x;
				owner_y = monitor_y;

				owner_width = monitor_width;
				owner_height = monitor_height;
			}
		}

		if (owner != NULL) {
			// Set the window position to the center of the owner monitor
			glfwSetWindowPos(window, owner_x + (owner_width * 0.5) - window_width, owner_y + (owner_height * 0.5) - window_height);
		}
	}
	glfwMakeContextCurrent(window);

	void Window::ScreenShot(std::string name)
	{
		stbi_flip_vertically_on_write(true);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) exit(EXIT_FAILURE);
}

		int width, height;
evolver::Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

		glfwGetFramebufferSize(window, &width, &height);
		uint8_t* ptr = (uint8_t*)malloc(width * height * 4);
void evolver::Window::ScreenShot(std::string name)
{
	stbi_flip_vertically_on_write(true);

		glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, ptr);
		stbi_write_png(name.c_str(), width, height, 4, ptr, 0);
	int width, height;

		std::cout << "Saved " + name << "\n";
	glfwGetFramebufferSize(window, &width, &height);
	uint8_t* ptr = (uint8_t*)malloc(width * height * 4);

		free(ptr);
	}
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, ptr);
	stbi_write_png(name.c_str(), width, height, 4, ptr, 0);

	bool Window::Loop()
	{
		return (!glfwWindowShouldClose(window));
	}
	std::cout << "Saved " + name << "\n";

	void Window::Swap()
	{
		glfwSwapBuffers(window);
	}
	free(ptr);
}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}
bool evolver::Window::Loop()
{
	return !glfwWindowShouldClose(window);
}

	void Window::Cleanup()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}
void evolver::Window::Swap()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

	GLFWwindow* Window::GetWindowPointer()
	{
		return window;
	}
void evolver::Window::Cleanup()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

	void Window::SetWindowPointer(GLFWwindow* window)
	{
		this->window = window;
	}
GLFWwindow* evolver::Window::GetWindowPointer()
{
	return window;
}

void evolver::Window::SetWindowPointer(GLFWwindow* window)
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
void evolver::Window::GetDetails()
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