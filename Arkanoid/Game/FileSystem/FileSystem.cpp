#include "FileSystem.h"
#include <iostream>

namespace Arkanoid
{
	UFileSystem::UFileSystem() {}

	// Save information in any file
	bool UFileSystem::Serialize(const std::string& Path, const std::vector<std::string>& Info)
	{
		Data.open(Path);

		if (!Data.is_open())
		{
			std::cout << "Error, couldn't open file: " << Path;
			return false;
		}
		else 
		{
			for (const auto& i : Info) 
			{
				Data << i;
			}

			Data.close();
			return true;
		}

		return false;
	}

	bool UFileSystem::Serialize(const std::string& Path, const std::vector<std::pair<std::string, int>>& Info)
	{
		Data.open(Path);

		if (!Data.is_open())
		{
			std::cout << "Error, couldn't open file: " << Path;
			return false;
		}
		else
		{
			for (const auto& i : Info)
			{
				Data << i.first << " " << i.second << std::endl;
			}

			Data.close();
			return true;
		}

		return false;
	}

	// Get information from any file
	bool UFileSystem::Deserialize(const std::string& Path, std::vector<std::string>& Info)
	{
		Data.open(Path);

		if (!Data.is_open())
		{
			std::cout << "Error, couldn't open file: " << Path;
			return false;
		}
		else
		{
			std::string Line;

			while (Data >> Line)
			{
				Info.push_back(Line);
			}

			Data.close();
			return true;
		}

		return false;
	}

	bool UFileSystem::Deserialize(const std::string& Path, std::vector<std::pair<std::string, int>>& Info)
	{
		Data.open(Path);

		if (!Data.is_open())
		{
			std::cout << "Error, couldn't open file: " << Path;
			return false;
		}
		else
		{
			std::string Name;
			int Score;

			while (Data >> Name >> Score)
			{
				Info.push_back({ Name, Score });
			}

			Data.close();
			return true;
		}

		return false;
	}
}