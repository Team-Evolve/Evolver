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
		void CopyTo(const std::string& path);
		void Rename(const std::string& newName);
		
		inline const char* GetConstChar();
		inline std::string GetString();

	private:
		std::filesystem::path filepath;
	};
}
