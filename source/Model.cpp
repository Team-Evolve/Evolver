#include  "../include/Model.h"

namespace evolver
{
	Model::Model(std::string path) : Object()
	{
		LoadModel(path);
	}

	void Model::Cleanup()
	{
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			meshes[i].Cleanup();
		}
	}

	void Model::LoadModel(std::string& modelFile)
	{
		if (!std::filesystem::exists(modelFile))
		{
			LOG_ERROR(modelFile + " Cannot Found");
			return;
		}

		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(modelFile, aiProcess_Triangulate |
																		aiProcess_FlipUVs |
																		aiProcess_CalcTangentSpace);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			LOG_ERROR("::ASSIMP::ERROR::");
			std::cout << importer.GetErrorString() << "\n";
			return;
		}

		ProcessNode(scene->mRootNode, scene);
	}
	
	void Model::ProcessNode(aiNode* node, const aiScene* scene)
	{
		aiMesh* mesh = nullptr;

		for (int i = 0; i < node->mNumMeshes; i++)
		{
			mesh = scene->mMeshes[node->mMeshes[i]];
			meshes.push_back(ProcessMesh(mesh, scene));
		}

		for (int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene);
		}
	}
	
	Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		VertexBufferAttributes vertex;
		unsigned int size = mesh->mNumVertices;
		glm::vec3 vector;
		glm::vec2 vec;

		std::vector<VertexBufferAttributes> vertices(size);
		std::vector<unsigned int> indices;

		for (unsigned int i = 0; i < size; i++)
		{
			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.position = vector;

			if (mesh->HasNormals())
			{
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.normal = vector;
			}

			if (mesh->mTextureCoords[0])
			{
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.textureCoordinates = vec;

				vector.x = mesh->mTangents[i].x;
				vector.y = mesh->mTangents[i].y;
				vector.z = mesh->mTangents[i].z;
				vertex.tangent = vector;

				vector.x = mesh->mBitangents[i].x;
				vector.y = mesh->mBitangents[i].y;
				vector.z = mesh->mBitangents[i].z;
			}
			else
			{
				vertex.textureCoordinates = glm::vec2(0.0f, 0.0f);
			}

			vertices[i] = vertex;
		}

		aiFace face;

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			face = mesh->mFaces[i];

			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		return Mesh(vertices, indices);
	}
	
	Model::~Model()
	{
		Cleanup();
	}

	void Model::Render()
	{
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			meshes[i].Draw();
		}
	}
}