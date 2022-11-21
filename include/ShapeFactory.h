#pragma once

#include <iostream>
#include <map>
#include "shapes/Cube.h"

namespace evolver
{
	class ShapeFactory
	{
	public:
		ShapeFactory();
		~ShapeFactory();

		void RenderCube();
		
	private:
		std::map<const char*, Object> objects;
	};
}
