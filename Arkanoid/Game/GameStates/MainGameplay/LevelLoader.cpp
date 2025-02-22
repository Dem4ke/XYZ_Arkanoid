#include "LevelLoader.h"
#include "GameObjects/BlockFactory.h"
#include "../../FileSystem/FileSystem.h"

namespace Arkanoid
{
	ULevelLoader::ULevelLoader() 
	{

	}

	// Load information of inputed level and create blocks and ball with platform
	void ULevelLoader::Load(int LevelIndex)
	{
		std::vector<std::string> BlocksText;
		std::string LevelNumberString = "Level " + std::to_string(LevelIndex);

		BlockFactories.emplace_back(std::make_shared<UNormalBlockFactory>);
		BlockFactories.emplace_back(std::make_shared<UThreeHitBlockFactory>);
		BlockFactories.emplace_back(std::make_shared<UUnbreakableBlockFactory>);

		UFileSystem FileSystem;
		FileSystem.Deserialize(Path, BlocksText);

		// Erase no needed lines from vector
		int LineToRemove = 0;

		for (auto& i : BlocksText)
		{
			++LineToRemove;
			int Found = i.find(LevelNumberString);

			if (Found != -1)
			{
				LineToRemove += 2;
				break;
			}
		}

		for (int i = BlocksText.size(); i > LineToRemove + 3; ++i)
		{
			BlocksText.erase(BlocksText.cbegin() + i);
		}

		for (int i = LineToRemove; i >= 0; ++i)
		{
			BlocksText.erase(BlocksText.cbegin() + i);
		}

		// Create all blocks
		GameObjects.emplace_back();
		
		// Create a ball and platform
	}

	const std::vector<std::shared_ptr<IGameObject>>& ULevelLoader::GetGameObjects()
	{
		return GameObjects;
	}

	const std::vector<std::shared_ptr<IGameObject>>& ULevelLoader::GetBlocks()
	{
		return Blocks;
	}
}