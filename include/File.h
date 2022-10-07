#pragma once

#include <filesystem>

namespace evolver
{
	class File
	{
	public:
		File() = delete;
		File(std::string path);
		File(const File& other) = delete;
		File(File&& other) = delete;
		File& operator=(File other) = delete;
		~File() = default;

		bool Exists();
		void Remove();
		void CopyTo(std::string path);
		void Rename(std::string newName);
		const char* GetPath();

	private:
		std::filesystem::path filepath;
	};
}
