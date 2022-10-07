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

	void File::CopyTo(std::string path)
	{
		std::filesystem::path tempPath(path);
		std::filesystem::copy_file(filepath, path);

		filepath.assign(path);
	}

	void File::Rename(std::string newName)
	{
		std::filesystem::path tempPath(newName);
		std::filesystem::rename(filepath, tempPath);

		filepath.assign(newName);
	}
	
	const char* File::GetPath()
	{
		return (filepath.string().c_str());
	}
}
