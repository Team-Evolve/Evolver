#include "include/Window.h"
#include "include/Shader.h"
#include "include/File.h"

int main()
{
	evolver::Window window(1280, 720);
	window.SetWindowAtCenter();

	std::string vertexShader = "shaders/test/test.vert";
	std::string fragmentShader = "shaders/test/test.frag";
	std::vector shaders = { vertexShader, fragmentShader };

	evolver::Shader testShader(shaders, "test");

	LOG_INFO("Window Initialized");

	while (window.Loop())
	{
		window.Swap();
		window.PollEvents();
	}

	window.Cleanup();

	return 0;
}