#include "../include/Sampler.h"

namespace evolver
{
	int Sampler::GetTexture2DValue(unsigned int textureID, int u, int v, int width, int height, GLenum type)
	{
		unsigned int* pixels = nullptr;
		glGetTextureImage(textureID, 0, GL_RGBA, type, width * height * sizeof(unsigned int), pixels);
		return pixels != nullptr ? pixels[u * width + v * height] : -1;
	}

	float Sampler::GetTextureHDRValue(unsigned int textureID, int u, int v, int width, int height)
	{
		float* pixels = nullptr;
		glGetTextureImage(textureID, 0, GL_RGBA, GL_FLOAT, width * height * sizeof(float), pixels);
		return pixels != nullptr ? pixels[u * width + v * height] : -1;
	}

	glm::vec2 Sampler::GetCubemapUV(glm::vec3 pos)
	{
		glm::vec3 posAbs = glm::abs(pos);
		float ma;
		glm::vec2 uv;

		if (posAbs.z >= posAbs.x && posAbs.z >= posAbs.y)
		{
			ma = 0.5f / posAbs.z;
			uv = glm::vec2(pos.z < 0.0 ? -pos.x : pos.x, -pos.y);
		}
		else if (posAbs.y >= posAbs.x)
		{
			ma = 0.5 / posAbs.y;
			uv = glm::vec2(pos.x, pos.y < 0.0 ? -pos.z : pos.z);
		}
		else
		{
			ma = 0.5 / posAbs.x;
			uv = glm::vec2(pos.x < 0.0 ? pos.z : -pos.z, -pos.y);
		}

		return glm::abs(uv);
	}

	template<typename T>
	T Sampler::GetCubemapValue(unsigned int textureID, glm::vec3 pos, int width, int height, GLenum format, GLenum type)
	{
		auto [uv, face] = GetCubemapValues(pos);

		GLint level = 0;

		switch (face)
		{
		case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
			level = 0;
			break;
		case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
			level = 1;
			break;
		case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
			level = 2;
			break;
		case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
			level = 3;
			break;
		case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
			level = 4;
			break;
		case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
			level = 5;
			break;
		}

		int index = uv.x * width + uv.y * height;

		switch (type)
		{
		case GL_UNSIGNED_INT:
			unsigned int* pixels = nullptr;
			glGetTextureImage(textureID, level, format, type, width * height * sizeof(unsigned int), pixels);
			return T(pixels[index]);
			break;
		case GL_FLOAT:
			float* pixels = nullptr;
			glGetTextureImage(textureID, level, format, type, width * height * sizeof(float), pixels);
			return T(pixels[index]);
		}

		return T();
	}

	std::pair<glm::vec2, GLenum> Sampler::GetCubemapValues(glm::vec3 pos)
	{
		// https://www.gamedev.net/forums/topic/687535-implementing-a-cube-map-lookup-function/5337472/

		GLenum face = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
		glm::vec3 posAbs = glm::abs(pos);
		float ma;
		glm::vec2 uv;

		if (posAbs.z >= posAbs.x && posAbs.z >= posAbs.y)
		{
			face = pos.z < 0.0 ? GL_TEXTURE_CUBE_MAP_NEGATIVE_Z : GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
			ma = 0.5f / posAbs.z;
			uv = glm::vec2(pos.z < 0.0 ? -pos.x : pos.x, -pos.y);
		}
		else if (posAbs.y >= posAbs.x)
		{
			face = pos.y < 0.0 ? GL_TEXTURE_CUBE_MAP_NEGATIVE_Y : GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
			ma = 0.5 / posAbs.y;
			uv = glm::vec2(pos.x, pos.y < 0.0 ? -pos.z : pos.z);
		}
		else
		{
			face = pos.x < 0.0 ? GL_TEXTURE_CUBE_MAP_NEGATIVE_X : GL_TEXTURE_CUBE_MAP_POSITIVE_X;
			ma = 0.5 / posAbs.x;
			uv = glm::vec2(pos.x < 0.0 ? pos.z : -pos.z, -pos.y);
		}

		return std::pair<glm::vec2, GLenum>(glm::abs(uv), face);
	}
}
