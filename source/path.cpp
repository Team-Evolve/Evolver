#include "../include/path.h"

namespace evolver
{
	Path::Path(std::string new_path) : path(new_path) 
	{}

	void Path::Change(const char* from, const char* to)
	{
		std::string pathStr = path.string();
		int seperator = '/';
		int counter = 0;

		for (char tempChar : pathStr)
		{
			if (tempChar == seperator)
			{
				counter++;
			}
		}

		if (counter == 0) return;
		
		std::vector<std::string> strings(counter);
		int index = 0;
		std::string tempStr = "";

		for (char tempChar : pathStr)
		{
			if (tempChar != seperator)
			{
				tempStr += tempChar;
			}
			else
			{
				strings[index] = tempStr;
				index++;
				tempStr = "";
			}
		}

		std::string result = "";
		std::string toStr = to;

		for (std::string str : strings)
		{
			std::string addToResult = strcmp(from, str.c_str()) == 0 ? (toStr + "/") : (str + "/");
			result += addToResult;
		}

		std::filesystem::path tempPath(result);
		path = tempPath;
	}

	std::string Path::GetString()
	{
		return path.string();
	}

	const char* Path::GetConstChar()
	{
		return (path.string().c_str());
	}
	
	std::filesystem::path Path::GetPath()
	{
		return path;
	}
	
	void Path::Reset()
	{
		std::filesystem::path nullPath("");
		path = nullPath;
	}
}