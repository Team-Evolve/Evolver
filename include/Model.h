#pragma once

#include "Mesh.h"
#include "Debug.h"
#include <filesystem>
#include <fstream>

namespace evolver
{
	class Model
	{
	public:
		Model() = delete;
		Model(std::string path);
		Model(const Model& other) = delete;
		Model(Model&& other) = delete;
		Model& operator=(Model other) = delete;
		~Model();

		void Draw();

	private:
		void Cleanup();

		void LoadModel(std::string& modelFile);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	private:
		std::vector<Mesh> meshes;
	};
}
