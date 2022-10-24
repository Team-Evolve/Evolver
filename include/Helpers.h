#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <filesystem>

static bool CheckIfExists(const char* directory, const char* filename)
{
	if (!std::filesystem::exists(directory))
	{
		return false;
	}

	for (const auto& entry : std::filesystem::directory_iterator(directory))
	{
		const char* pathChar = entry.path().string().c_str();

		if (strstr(filename, pathChar) == 0)
		{
			return true;
		}
	}

	return false;
}

inline std::string Vec3ToString(glm::vec3 vec)
{
	return (std::to_string(vec.x) + " " + std::to_string(vec.y) + " " + std::to_string(vec.z));
}

inline std::string Vec2ToString(glm::vec2 vec)
{
	return (std::to_string(vec.x) + " " + std::to_string(vec.y));
}