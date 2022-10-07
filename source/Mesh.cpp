#include "../include/Mesh.h"

namespace evolver
{
	Mesh::Mesh(std::vector<VertexBufferAttributes>& vertAttr, std::vector<unsigned int>& index, std::vector<TextureAttributes>& texAttr)
	{
		vertexAttributes = std::make_unique<VertexBufferAttributes*>(vertAttr.data());
		size_vertex = vertAttr.size();

		indices = std::make_unique<unsigned int*>(index.data());
		size_indices = index.size();

		textureAttributes = std::make_unique<TextureAttributes*>(texAttr.data());
		size_texture = texAttr.size();

		VAO = 0; VBO = 0; EBO = 0;

		SetupMesh();
	}

	Mesh::~Mesh()
	{
		size_vertex = 0;
		size_indices = 0;
		size_texture = 0;

		if (VAO)
		{
			glDeleteVertexArrays(1, &VAO);
		}

		if (VBO)
		{
			glDeleteBuffers(1, &VBO);
		}

		if (EBO)
		{
			glDeleteBuffers(1, &EBO);
		}

		vertexAttributes.release();
		indices.release();
		textureAttributes.release();
	}

	void Mesh::Draw()
	{
		if (VAO == 0) return;

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, size_indices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void Mesh::SetupMesh()
	{
		size_t sizeVertexAttributes = sizeof(VertexBufferAttributes);

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, size_vertex * sizeVertexAttributes, &(vertexAttributes.get())[0], GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_indices * sizeof(unsigned int), &(indices.get())[0], GL_STATIC_DRAW);

		// vertex buffer location = 0 | Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeVertexAttributes, (void*)0);
		glEnableVertexAttribArray(0);

		// vertex buffer location = 1 | Normal
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeVertexAttributes, (void*)offsetof(VertexBufferAttributes, normal));
		glEnableVertexAttribArray(1);

		// vertex buffer location = 2 | Texture Coordinate
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeVertexAttributes, (void*)offsetof(VertexBufferAttributes, textureCoordinates));
		glEnableVertexAttribArray(2);

		// vertex buffer location = 3 | Tangent Coordinates
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeVertexAttributes, (void*)offsetof(VertexBufferAttributes, tangent));
		glEnableVertexAttribArray(3);

		// vertex buffer location = 4 | Bitangent Coordinates
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeVertexAttributes, (void*)offsetof(VertexBufferAttributes, bitangent));
		glEnableVertexAttribArray(4);

		glBindVertexArray(0);
	}
}
