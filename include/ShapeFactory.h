#pragma once

#include <glad/glad.h>

namespace evolver
{
	class ShapeFactory
	{
	public:
		ShapeFactory();
		~ShapeFactory();
		void RenderCube();

	private:
		unsigned int cubeVAO, cubeVBO;
	};
}
