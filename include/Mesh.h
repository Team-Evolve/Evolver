#pragma once

#include "Helpers.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include <vector>
#include <memory>

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
		Mesh(std::vector<VertexBufferAttributes>& vertAttr, std::vector<unsigned int>& index);
		Mesh(const Mesh& other) = delete;
		Mesh(Mesh&& other) = delete;
		Mesh& operator=(Mesh other) = delete;
		~Mesh();

		void Draw();
		void Cleanup();

		std::string GetVertexAttributeString();
		std::string GetIndexBufferString();

	private:
		void SetupMesh();

	private:
		std::unique_ptr<VertexBufferAttributes> vertexAttributes;
		std::unique_ptr<unsigned int> indices;

		unsigned int size_vertex, size_indices;
		unsigned int VAO, VBO, EBO;
	};
}
