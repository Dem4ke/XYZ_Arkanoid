#include <algorithm>
#include "LeaderBoard.h"
#include "../../FileSystem/FileSystem.h"

namespace Arkanoid
{
	ULeaderBoard::ULeaderBoard()
	{
		Load();
	}

	// Save sorted table to txt file
	void ULeaderBoard::Save()
	{
		UFileSystem FileSystem;
		FileSystem.Serialize(Path, Table);
	}

	// Add new player in table and sort it
	void ULeaderBoard::AddPlayer(std::pair<std::string, int> Player)
	{
		Table.push_back(Player);
		Sort();
	}

	// Get table to draw it
	const std::vector<std::pair<std::string, int>>& ULeaderBoard::GetTable()
	{
		return Table;
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	      PRIVATE WORKTOOLS         */
	/*                                  */
	/*//////////////////////////////////*/

	// Load table from txt file
	void ULeaderBoard::Load()
	{
		UFileSystem FileSystem;
		FileSystem.Deserialize(Path, Table);
	}

	// Sort table by decreasing order (from biggest to less)
	void ULeaderBoard::Sort()
	{
		auto cmp = [](std::pair<std::string, int> const& a, std::pair<std::string, int> const& b) 
		{
			return a.second > b.second;
		};

		std::sort(std::begin(Table), std::end(Table), cmp);
	}
}