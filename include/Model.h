#pragma once

#include "Mesh.h"
#include "File.h"

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
	};
}
