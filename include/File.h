#pragma once

#include <filesystem>

namespace evolver
{
	class File
	{
	public:
		File() = default;
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
		inline void Reset() { filepath = ""; }

		void operator+=(std::string& addPath)
		{
			filepath += addPath;
		}

		void operator+=(File& addPath)
		{
			filepath += (addPath.GetString());
		}

		void operator+=(const char* addPath)
		{
			filepath += addPath;
		}

		void operator=(const char* name)
		{
			filepath = name;
		}

		void operator=(std::string& name)
		{
			filepath = name;
		}

		void operator=(File& name)
		{
			filepath = name.GetString();
		}

	private:
		std::filesystem::path filepath;
	};
}
