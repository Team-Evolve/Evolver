#include "../include/Window.h"

void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
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
		if (!glfwInit())
		{
			LOG_ERROR("Cannot Initialize GLFW Init");
			exit(EXIT_FAILURE);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);

#if defined(__APPLE__)
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

		if (major == 4 && minor >= 5)
		{
			#define GL_4_5_OR_NEWER
		}

		window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

		if (window == nullptr)
		{
			LOG_ERROR("Window Pointer Cannot Initialized");
			return;
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_ERROR("Cant Load GLAD");
			exit(EXIT_FAILURE);
		}

		glfwSetKeyCallback(window, Key_Callback);
	}

	Window::~Window()
	{
		Cleanup();
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

	void Window::ScreenShot(std::string name)
	{
		stbi_flip_vertically_on_write(true);

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		uint8_t* ptr = (uint8_t*)malloc(width * height * 4);

		glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, ptr);
		stbi_write_png(name.c_str(), width, height, 4, ptr, 0);

		LOG_INFO("Saved " + name);

		free(ptr);
	}

	bool Window::Loop()
	{
		return (!glfwWindowShouldClose(window));
	}

	void Window::Swap()
	{
		glfwSwapBuffers(window);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::Cleanup()
	{
		if (window != nullptr)
		{
			glfwDestroyWindow(window);
			glfwTerminate();
		}
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