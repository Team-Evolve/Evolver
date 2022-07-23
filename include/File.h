#pragma once

#include "path.h"

namespace evolver
{
	class File
	{
	public:
		File() = default;
		File(std::string file);
		~File() = default;

	public:
		void SetPath(Path newPath) { filepath = newPath; }

		bool IsFileExists();
		void Rename(Path newName);
		void CopyFile(Path newPath);
		void CopyDirectory(Path newPath);
		void Remove();
		void RemoveAll();

	private:
		Path filepath;
	};
}