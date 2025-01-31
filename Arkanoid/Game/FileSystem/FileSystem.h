#pragma once
#include <fstream>
#include <vector>

namespace Arkanoid
{
	class UFileSystem 
	{
	public:
		UFileSystem();

		bool Serialize(const std::string& Path, const std::vector<std::string>& Info);
		bool Deserialize(const std::string& Path, std::vector<std::string>& Info);

	private:
		std::fstream Data;
	};
}