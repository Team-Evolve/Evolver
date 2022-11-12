#pragma once

#include "Helpers.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include <vector>
#include <fstream>

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

	class Mesh
	{
	public:
		Mesh() = default;
		Mesh(std::vector<VertexBufferAttributes>& vertAttr, std::vector<unsigned int>& index);
		~Mesh();

		void Draw();
		void Cleanup();

	private:
		void SetupMesh(std::vector<VertexBufferAttributes>& vertexAttributes, std::vector<unsigned int>& indices);

	private:
		unsigned int size_vertex, size_indices;
		unsigned int VAO, VBO, EBO;
	};
}
