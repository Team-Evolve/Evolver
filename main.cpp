#include "include/Window.h"

int main()
{
	evolver::Window window(1280, 720);
	window.SetWindowAtCenter();

	LOG_INFO("Window Initialized");

	while (window.Loop())
	{
		window.Swap();
		window.PollEvents();
	}

	window.Cleanup();

	return 0;
}