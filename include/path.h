#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

namespace evolver
{
	class Path
	{
	public:
		Path() = default;
		Path(std::string new_path);
		~Path() = default;

	public:
		void operator+=(const char* toAdd)
		{
			int wantedLastCharacter = '/';
			std::string temp = toAdd;

			if (temp.back() != wantedLastCharacter)
			{
				temp += "/";
			}

			path += temp;
		}

		std::string GetString();
		const char* GetConstChar();
		std::filesystem::path GetPath();
		void Reset();
		void Change(const char* from, const char* to);

	private:
		std::filesystem::path path;
	};
}