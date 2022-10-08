#include "../include/File.h"

namespace evolver
{
	File::File(std::string path)
	{
		filepath.assign(path);
	}

	bool File::Exists()
	{
		return std::filesystem::exists(filepath);
	}

	void File::Remove()
	{
		std::filesystem::remove(filepath);
	}

	void File::CopyTo(const std::string& path)
	{
		std::filesystem::path tempPath(path);
		std::filesystem::copy_file(filepath, path);

		filepath.assign(path);
	}

	void File::Rename(const std::string& newName)
	{
		std::filesystem::path tempPath(newName);
		std::filesystem::rename(filepath, tempPath);

		filepath.assign(newName);
	}
	
	const char* File::GetConstChar()
	{
		return (filepath.string().c_str());
	}

	inline std::string File::GetString()
	{
		return (filepath.string());
	}
}
