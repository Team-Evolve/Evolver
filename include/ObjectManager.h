#pragma once

#include <iostream>
#include <map>
#include "Transform.h"
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
		/*
		void UpdateTime(double elapsedTime) { time += elapsedTime; }
		void CheckObjectRenderTime(double checkTime, double targetFPS);
		*/
		
	private:
		struct ObjectRecord
		{
			ObjectRecord()
			{
				object = nullptr;
				// renderTime = 0;
			}

			Object* object;
			// unsigned int renderTime;
		};

		Cube cube;
		std::map<const char*, ObjectRecord> objects;
		// double time;
	};
}
