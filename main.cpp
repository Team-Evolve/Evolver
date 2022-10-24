#include "include/Window.h"
#include "include/Shader.h"
#include "include/Model.h"

int main()
{
	evolver::Window window(1280, 720);
	window.SetWindowAtCenter();
	
	evolver::Shader testShader({ "shaders/test/test.vert", "shaders/test/test.frag" }, "test", true);
	evolver::Model testModel("models/test/dragon.obj");

	LOG_INFO("Window Initialized");

	while (window.Loop())
	{
		window.Swap();
		window.PollEvents();
	}

	return 0;
}