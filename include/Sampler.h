#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace evolver
{
	class Sampler
	{
	public:
		int GetTexture2DValue(unsigned int textureID, int u, int v, int width, int height, GLenum type);
		template<typename T>
		T GetCubemapValue(unsigned int textureID, glm::vec3 pos, int width, int height, GLenum format, GLenum type);
		float GetTextureHDRValue(unsigned int textureID, int u, int v, int width, int height);
		glm::vec2 GetCubemapUV(glm::vec3 pos);

	private:
		std::pair<glm::vec2, GLenum> GetCubemapValues(glm::vec3 pos);
	};
}
