#pragma once

#include "Shader.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include <vector>

namespace evolver
{
	struct VertexBufferAttributes
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 textureCoordinates;
		glm::vec3 tangent;
		glm::vec3 bitangent;
	};

	struct TextureAttributes
	{
		unsigned int textureID;
		std::string textureType;
		aiString path;
	};

	class Mesh
	{
	public:
		Mesh() = delete;
		Mesh(std::vector<VertexBufferAttributes>& vertAttr, std::vector<unsigned int>& index, std::vector<TextureAttributes>& texAttr);
		Mesh(const Mesh& other) = delete;
		Mesh(Mesh&& other) = delete;
		Mesh& operator=(Mesh other) = delete;
		~Mesh();

		void Draw();
		void Cleanup();

	private:
		void SetupMesh();

	private:
		std::unique_ptr<VertexBufferAttributes*> vertexAttributes;
		std::unique_ptr<unsigned int*> indices;
		std::unique_ptr<TextureAttributes*> textureAttributes;
		unsigned int size_vertex, size_indices, size_texture;
		unsigned int VAO, VBO, EBO;
	};
}
