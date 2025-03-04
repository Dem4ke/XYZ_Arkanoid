#pragma once

#include <vector>
#include <memory>
#include <string>

namespace Arkanoid
{
	class UBlock;
	class IGameObject;
	class IBlockFactory;

	class ULevelLoader final
	{
	public:
		ULevelLoader() = default;
		~ULevelLoader() = default;

		void Load(int LevelIndex);
		int GetCurrentLevel() const;
		int GetBreackableBlocksCount() const;

		const std::vector<std::shared_ptr<IGameObject>>& GetGameObjects();
		const std::vector<std::shared_ptr<UBlock>>& GetBlocks();

	private:
		int CurrentLevel = 1;
		int BreakableBlocks = 0;										// Count of breakable blocks on level

		std::vector<std::shared_ptr<IBlockFactory>> BlockFactories;		// Block factories to create all blocks
		std::vector<std::shared_ptr<IGameObject>> GameObjects;			// Vector of playable objects (ball, platform)
		std::vector<std::shared_ptr<UBlock>> Blocks;					// Vector of blocks

		const std::string Path = "Config/Levels.conf";					// Path to levels config file
	};
}