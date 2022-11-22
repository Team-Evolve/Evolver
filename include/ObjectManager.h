#pragma once

#include <iostream>
#include <map>
#include "shapes/Cube.h"

namespace evolver
{
	class ObjectManager
	{
	public:
		ObjectManager();
		~ObjectManager();

		void AddObject(const char* name, Object* object);
		void RenderObject(const char* name);
		void RenderCube();
		
	private:
		Cube cube;
		std::map<const char*, Object*> objects;
	};
}
