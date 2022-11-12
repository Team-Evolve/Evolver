#include "../include/Mesh.h"

namespace evolver
{
	Mesh::Mesh(std::vector<VertexBufferAttributes>& vertAttr, std::vector<unsigned int>& index)
	{
		size_vertex = vertAttr.size();
		vertexAttributes.resize(size_vertex);
		memcpy(vertexAttributes.data(), vertAttr.data(), size_vertex * sizeof(VertexBufferAttributes));

		size_indices = index.size();
		indices.resize(size_indices);
		memcpy(indices.data(), index.data(), size_indices * sizeof(unsigned int));

		VAO = 0; VBO = 0; EBO = 0;

		SetupMesh();
	}

	Mesh::~Mesh()
	{
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
		glBufferData(GL_ARRAY_BUFFER, size_vertex * sizeVertexAttributes, &(vertexAttributes[0]), GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_indices * sizeof(unsigned int), &(indices[0]), GL_STATIC_DRAW);

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

	void Mesh::Cleanup()
	{
		if (size_vertex != 0)
		{
			vertexAttributes.clear();
		}

		if (indices.size() != 0)
		{
			indices.clear();
		}
	
		size_vertex = 0;
	}

	/*
	void Mesh::WriteVertexAttributes(std::string& filename)
	{
		auto file = std::fstream(filename, std::ios::out | std::ios::binary);
		std::string temp;
		VertexBufferAttributes vertex;

		for (unsigned int i = 0; i < size_vertex; i++)
		{
			vertex = vertexAttributes[i];

			temp = (Vec3ToString(vertex.position) + " " + Vec3ToString(vertex.normal) + " " + Vec2ToString(vertex.textureCoordinates)
				+ " " + Vec3ToString(vertex.tangent) + " " + Vec3ToString(vertex.bitangent) + "\n");

			file.write(temp.c_str(), temp.length());
		}

		file.close();
	}

	std::string Mesh::GetIndexBufferString()
	{
		std::string temp;

		for (unsigned int i = 0; i < size_indices; i++)
		{
			temp += std::to_string(indices[i]);
		}

		return temp;
	}
	*/
}
