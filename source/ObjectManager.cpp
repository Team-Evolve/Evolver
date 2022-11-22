#include "../include/ObjectManager.h"

namespace evolver
{
	ObjectManager::ObjectManager()
	{
		objects.insert({ "cube", &cube});
	}

	ObjectManager::~ObjectManager()
	{
		for (auto [name, object] : objects)
		{
			object->Cleanup();
		}
	}

	void ObjectManager::AddObject(const char* name, Object* object)
	{
		objects.insert({ name, object });
	}

	void ObjectManager::RenderObject(const char* name)
	{
		if (auto object = objects.find(name); object != objects.end())
		{
			Object* pObject = object->second;
			pObject->Render();
		}
	}

	void ObjectManager::RenderCube()
	{
		if (auto object = objects.find("cube"); object != objects.end())
		{
			Object* pObject = object->second;
			pObject->Render();
		}
	}
}