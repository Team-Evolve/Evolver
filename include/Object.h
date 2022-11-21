#pragma once

#include <iostream>
#include <glad/glad.h>

namespace evolver
{
	class Object
	{
	public:
		void Render() {};
		void Cleanup() {};

		unsigned int VAO, VBO;
	};
}
