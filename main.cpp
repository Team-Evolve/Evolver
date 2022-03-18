#include "../include/Window.h"

int main()
{
	evolver::Window window(1280, 720);

	while (window.Loop())
	{
		window.Swap();
	}

	return 0;
}