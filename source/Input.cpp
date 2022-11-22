#include "../include/Input.h"

namespace evolver
{
	void Input::SetKeyAndAction(int key, std::function<void()> actionFunc)
	{
		keys.insert({ key, actionFunc });
	}

	void Input::ExecuteKeys()
	{
		for (auto [key, actionFunc] : keys)
		{
			if (key && GLFW_PRESS)
			{
				actionFunc();
			}
		}
	}
}