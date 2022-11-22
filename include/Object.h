#pragma once

#include <iostream>
#include <glad/glad.h>

namespace evolver
{
	class Object
	{
	public:
		Object() { VAO = 0; VBO = 0; };

		virtual void Render() {};
		virtual void Cleanup() {};

	protected:
		unsigned int VAO, VBO;
	};
}
