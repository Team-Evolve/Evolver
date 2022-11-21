#include "../include/ShapeFactory.h"

namespace evolver
{
	ShapeFactory::ShapeFactory()
	{
		objects.insert({ "cube", Cube()});
	}

	ShapeFactory::~ShapeFactory()
	{
		for (auto [name, object] : objects)
		{
			object.Cleanup();
		}
	}

	void ShapeFactory::RenderCube()
	{
		if (auto object = objects.find("cube"); object != objects.end())
		{
			(object->second).Render();
		}
	}
}