#pragma once

#include <GLFW/glfw3.h>
#include <map>
#include <functional>

namespace evolver
{
	class Input
	{
	public:
		void SetKeyAndAction(int key, std::function<void()> actionFunc);
		void ExecuteKeys();

	private:
		std::map<int, std::function<void()>> keys;
	};
}