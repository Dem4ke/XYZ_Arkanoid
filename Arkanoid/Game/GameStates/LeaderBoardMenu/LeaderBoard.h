#pragma once

#include <vector>
#include <string>

namespace Arkanoid
{
	class ULeaderBoard
	{
	public:
		ULeaderBoard();
		~ULeaderBoard() = default;

		void Save();
		void AddPlayer(std::pair<std::string, int> Player);

		const std::vector<std::pair<std::string, int>>& GetTable();

	private:
		void Load();
		void Sort();

		std::vector<std::pair<std::string, int>> Table;		// Sorted vector of all players with their score
		const std::string Path = "Data/LeaderTable.txt";	// Path to the file which contains "Table" above
	};
}