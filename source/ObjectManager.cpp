#include "../include/ObjectManager.h"

namespace evolver
{
	ObjectManager::ObjectManager()
	{
		time = 0.0;

		ObjectRecord cubeObjectRecord;
		cubeObjectRecord.object = &cube;

		objects.insert({ "cube", cubeObjectRecord});
	}

	ObjectManager::~ObjectManager()
	{
		for (auto [name, object] : objects)
		{
			(object.object)->Cleanup();
		}
	}

	void ObjectManager::AddObject(const char* name, Object* object)
	{
		ObjectRecord tempObjectRecord;
		tempObjectRecord.object = object;

		objects.insert({ name, tempObjectRecord });
	}

	void ObjectManager::RenderObject(const char* name)
	{
		if (auto object = objects.find(name); object != objects.end())
		{
			Object* pObject = (object->second).object;
			pObject->Render();
			(object->second).renderTime += 1;
		}
	}

	void ObjectManager::RenderCube()
	{
		if (auto object = objects.find("cube"); object != objects.end())
		{
			Object* pObject = (object->second).object;
			pObject->Render();
			(object->second).renderTime += 1;
		}
	}

	void ObjectManager::CheckObjectRenderTime(double checkTime, double targetFPS)
	{
		if (time < checkTime) return;

		unsigned int requiredRenderTime = checkTime * targetFPS;

		for (auto [name, object] : objects)
		{
			if (object.renderTime < requiredRenderTime)
			{
				(object.object)->Cleanup();

				objects.erase(name);
			}
			else
			{
				object.renderTime = 0;
			}
		}
	}
}