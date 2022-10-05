#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <stb-image/stb_image.h>
#include <stb-image/stb_image_write.h>
#include <glad/glad.h>
#include "Debug.h"

namespace evolver
{
	enum EV_TexType
	{
		EV_TT_TEXTURE_2D,
		EV_TT_CUBEMAP,
		EV_TT_HDR
	};

	class Texture
	{
	public:
		Texture();
		~Texture();

		void Load2D(const std::string textureFilename, const std::string textureName, int* _width = nullptr, int* _height = nullptr);
		void LoadCubemap(std::vector<std::string> faces, const std::string cubemapName);
		void LoadHDR(const std::string hdrFilename, const std::string hdrName);

		void SaveTexture2D(const std::string name, int location, std::string path, int width, int height, GLenum format = GL_RGB, GLenum type = GL_UNSIGNED_BYTE);

		void Bind(const std::string name, const unsigned int location, EV_TexType texType = EV_TT_TEXTURE_2D);

		inline unsigned int GetTexture2DID(const std::string name);
		inline unsigned int GetCubemapID(const std::string name);
		inline unsigned int GetHDRTextureID(const std::string name);

	private:
		GLenum GetTexFormat(int channel);

	private:
		std::map<std::string, unsigned int> tex2DMap;
		std::map<std::string, unsigned int> texCubemapMap;
		std::map<std::string, unsigned int> texHDRMap;
	};
}