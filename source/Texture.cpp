#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../include/Texture.h"

evolver::Texture::Texture() {}

evolver::Texture::~Texture()
{
	for (const auto& [name, id] : tex2DMap)
		glDeleteTextures(1, &id);

	for (const auto& [name, id] : texCubemapMap)
		glDeleteTextures(1, &id);

	for (const auto& [name, id] : texHDRMap)
		glDeleteTextures(1, &id);
}

GLenum evolver::Texture::GetTexFormat(int channel)
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
	}
}

void evolver::Texture::Load2D(const std::string textureFilename, const std::string textureName, int* _width, int* _height)
{
	unsigned int temp2D;
	glGenTextures(1, &temp2D);

	stbi_set_flip_vertically_on_load(true);

	int width, height, channel;
	unsigned char* tex = stbi_load(textureFilename.c_str(), &width, &height, &channel, 0);

	if (tex)
	{
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

        #if _DEBUG
		std::cout << "Texture " << textureName << "loaded\n";
		#endif

		stbi_image_free(tex);

		tex2DMap.insert({ textureName, temp2D });
	}
	else
	{
        #if _DEBUG
		std::cout << "Can't Load Texture " << textureName << "\n";
        #endif

		return;
	}
}

void evolver::Texture::LoadCubemap(std::vector<std::string> faces, const std::string cubemapName)
{
	unsigned int tempCubemap;

	glGenTextures(1, &tempCubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tempCubemap);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);

		if (data)
		{
			GLenum texFormat = GetTexFormat(nrChannels);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, texFormat, width, height, 0, texFormat, GL_UNSIGNED_BYTE, data);
			#if _DEBUG
			std::cout << "Texture For Cubemap " << faces[i] << " Loaded\n";
			#endif
			stbi_image_free(data);
		}
		else
		{
			#if _DEBUG
			std::cout << "Cant Load Texture For Cubemap " << faces[i] << "\n";
			#endif
			stbi_image_free(data);

			return;
		}
	}

	#if _DEBUG
	std::cout << cubemapName << " Loaded\n";
	#endif

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	texCubemapMap.insert({ cubemapName, tempCubemap });
}

void evolver::Texture::LoadHDR(const std::string hdrFilename, const std::string hdrName)
{
	unsigned int tempHDR;
	int width, height, nrComponents;
	float* data = stbi_loadf(hdrFilename.c_str(), &width, &height, &nrComponents, 0);

	if (data)
	{
		glGenTextures(1, &tempHDR);
		glBindTexture(GL_TEXTURE_2D, tempHDR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		#if _DEBUG
		std::cout << "Texture " << hdrName << "loaded\n";
		#endif

		stbi_image_free(data);

		texHDRMap.insert({ hdrName, tempHDR });
	}
	else
	{
		#if _DEBUG
		std::cout << "Can't Load Texture " << textureName << "\n";
		#endif

		return;
	}
}

void evolver::Texture::Bind(const std::string name, const unsigned int location, EV_TexType texType)
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

unsigned int evolver::Texture::GetTexture2DID(const std::string name)
{
	return tex2DMap[name];
}

unsigned int evolver::Texture::GetCubemapID(const std::string name)
{
	return texCubemapMap[name];
}

unsigned int evolver::Texture::GetHDRTextureID(const std::string name)
{
	return texHDRMap[name];
}

void evolver::Texture::SaveTexture2D(const std::string name, const int location, const std::string path, const int width, const int height, GLenum format, GLenum type)
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

	#if _DEBUG
	std::cout << name << " saved to " << path << "\n";
	#endif

	free(ptr);
}