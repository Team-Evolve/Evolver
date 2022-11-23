#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#pragma warning(disable:4996)

#include "../include/TextureManager.h"

namespace evolver
{
	TextureManager::TextureManager() {}

	TextureManager::~TextureManager()
	{
		for (const auto& [name, id] : tex2DMap)
			glDeleteTextures(1, &id);

		for (const auto& [name, id] : texCubemapMap)
			glDeleteTextures(1, &id);

		for (const auto& [name, id] : texHDRMap)
			glDeleteTextures(1, &id);
	}

	GLenum TextureManager::GetTexFormat(int channel)
	{
		switch (channel)
		{
		case 1:
			return GL_RED;
			break;
		case 3:
			return GL_RGB;
			break;
		case 4:
			return GL_RGBA;
			break;
		default:
			return GL_RGBA;
			break;
		}
	}

	void TextureManager::Load2D(const std::string& textureFilename, const std::string& textureName, int* _width, int* _height)
	{
		unsigned int temp2D;
		glGenTextures(1, &temp2D);

		stbi_set_flip_vertically_on_load(true);

		int width, height, channel;
		unsigned char* tex = stbi_load(textureFilename.c_str(), &width, &height, &channel, 0);

		if (!tex)
		{
			LOG_ERROR("Can't Load Texture " + textureName);

			return;
		}

		GLenum texFormat = GetTexFormat(channel);

		glBindTexture(GL_TEXTURE_2D, temp2D);
		glTexImage2D(GL_TEXTURE_2D, 0, texFormat, width, height, 0, texFormat, GL_UNSIGNED_BYTE, tex);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (_width != nullptr && _height != nullptr)
		{
			*_width = width;
			*_height = height;
		}
			
		LOG_INFO("Texture " + textureName + "loaded");

		stbi_image_free(tex);

		tex2DMap.insert({ textureName, temp2D });
	}

	void TextureManager::LoadCubemap(std::vector<std::string>& faces, const std::string& cubemapName)
	{
		unsigned int tempCubemap;

		glGenTextures(1, &tempCubemap);
		glBindTexture(GL_TEXTURE_CUBE_MAP, tempCubemap);

		int width, height, nrChannels;
		unsigned char* data = nullptr;
		for (unsigned int i = 0; i < faces.size(); i++)
		{
			data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);

			if (!data)
			{
				LOG_ERROR("Cant Load Texture For Cubemap " + faces[i]);

				return;
			}

			GLenum texFormat = GetTexFormat(nrChannels);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, texFormat, width, height, 0, texFormat, GL_UNSIGNED_BYTE, data);

			LOG_INFO("Texture For Cubemap " + faces[i] + " Loaded");

			stbi_image_free(data);
		}

		LOG_INFO(cubemapName + " Loaded");

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		texCubemapMap.insert({ cubemapName, tempCubemap });
	}

	void TextureManager::LoadHDR(const std::string& hdrFilename, const std::string& hdrName)
	{
		unsigned int tempHDR;
		int width, height, nrComponents;
		float* data = stbi_loadf(hdrFilename.c_str(), &width, &height, &nrComponents, 0);

		if (!data)
		{
			LOG_ERROR("Can't Load Texture " + hdrName);

			return;
		}

		glGenTextures(1, &tempHDR);
		glBindTexture(GL_TEXTURE_2D, tempHDR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		LOG_INFO("Texture " + hdrName + "loaded\n");

		stbi_image_free(data);

		texHDRMap.insert({ hdrName, tempHDR });
	}

	void TextureManager::Bind(const std::string& name, const unsigned int location, EV_TexType texType)
	{
		switch (texType)
		{
		case EV_TT_TEXTURE_2D:
			glActiveTexture(GL_TEXTURE0 + location);
			glBindTexture(GL_TEXTURE_2D, tex2DMap[name]);
			break;
		case EV_TT_CUBEMAP:
			glActiveTexture(GL_TEXTURE0 + location);
			glBindTexture(GL_TEXTURE_CUBE_MAP, texCubemapMap[name]);
			break;
		case EV_TT_HDR:
			glActiveTexture(GL_TEXTURE0 + location);
			glBindTexture(GL_TEXTURE_2D, texHDRMap[name]);
			break;
		}
	}

	unsigned int TextureManager::GetTexture2DID(const std::string& name)
	{
		return tex2DMap[name];
	}

	unsigned int TextureManager::GetCubemapID(const std::string& name)
	{
		return texCubemapMap[name];
	}

	unsigned int TextureManager::GetHDRTextureID(const std::string& name)
	{
		return texHDRMap[name];
	}

	void TextureManager::SaveTexture2D(const std::string& name, const int location, const std::string& path, const int width, const int height, GLenum format, GLenum type)
	{
		stbi_flip_vertically_on_write(true);

		int size;
		int channel;
		switch (format)
		{
		case GL_R:
			size = width * height;
			channel = 1;
			break;
		case GL_RGB:
			size = width * height * 3;
			channel = 3;
			break;
		case GL_RGBA:
			size = width * height * 4;
			channel = 4;
			break;
		}

		uint8_t* ptr = (uint8_t*)malloc(size);

		glActiveTexture(GL_TEXTURE0 + location);
		glBindTexture(GL_TEXTURE_2D, tex2DMap[name]);
		glGetTexImage(GL_TEXTURE_2D, 0, format, type, ptr);

		stbi_write_png(path.c_str(), width, height, channel, ptr, 0);

		LOG_INFO(name + " saved to " + path);

		free(ptr);
	}
}