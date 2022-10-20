#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

inline std::string Vec3ToString(glm::vec3 vec)
{
	return (std::to_string(vec.x) + " " + std::to_string(vec.y) + " " + std::to_string(vec.z));
}

inline std::string Vec2ToString(glm::vec2 vec)
{
	return (std::to_string(vec.x) + " " + std::to_string(vec.y));
}