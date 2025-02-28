#pragma once

#include <vector>
#include <memory>
#include <string>

namespace Arkanoid
{
	class IGameObject;
	class IBlockFactory;

	class ULevelLoader final
	{
	public:
		ULevelLoader() = default;
		~ULevelLoader() = default;

		void Load(int LevelIndex);

		const std::vector<std::shared_ptr<IGameObject>>& GetGameObjects();
		const std::vector<std::shared_ptr<IGameObject>>& GetBlocks();

	private:
		std::vector<std::shared_ptr<IBlockFactory>> BlockFactories;		// Block factories to create all blocks
		std::vector<std::shared_ptr<IGameObject>> GameObjects;			// Vector of playable objects (ball, platform)
		std::vector<std::shared_ptr<IGameObject>> Blocks;				// Vector of blocks

		const std::string Path = "Config/Levels.conf";					// Path to levels config file
	};
}