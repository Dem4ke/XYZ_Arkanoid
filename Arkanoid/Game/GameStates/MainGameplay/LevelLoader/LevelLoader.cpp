#include <cassert>
#include "LevelLoader.h"
#include "../IGameObject.h"
#include "../GameObjects/BlockFactory.h"
#include "../GameObjects/Ball.h"
#include "../GameObjects/Platform.h"
#include "../../../FileSystem/FileSystem.h"
#include "../../../Settings/Settings.h"

namespace Arkanoid
{
	// Load information of inputed level and create blocks and ball with platform
	void ULevelLoader::Load(int LevelIndex)
	{
		BlockFactories.clear();
		GameObjects.clear();
		Blocks.clear();
		++CurrentLevel;

		// Load blocks configuration from file
		std::vector<std::string> BlocksText;
		std::string LevelNumberText = std::to_string(LevelIndex);

		UFileSystem FileSystem;
		FileSystem.Deserialize(Path, BlocksText);

		// Create factories of blocks
		BlockFactories.emplace_back(std::make_shared<UNormalBlockFactory>());
		BlockFactories.emplace_back(std::make_shared<UThreeHitBlockFactory>());
		BlockFactories.emplace_back(std::make_shared<UUnbreakableBlockFactory>());

		// Erase no needed lines from vector
		int LineToRemove = 0;

		// Find start of needed block of lines
		for (int i = 0, end = BlocksText.size(); i < end; ++i)
		{
			int FoundLevelText = BlocksText[i].find("Level");

			if (FoundLevelText != -1)
			{
				int Found = BlocksText[i + 1].find(LevelNumberText);

				if (Found != -1)
				{
					LineToRemove = i + 1;
					break;
				}
			}

			++LineToRemove;
		}

		// Erase lines before level's block
		for (int i = LineToRemove; i >= 0; --i)
		{
			BlocksText.erase(BlocksText.cbegin() + i);
		}

		LineToRemove = 0;

		// Find end of needed block of lines
		for (int i = 0, end = BlocksText.size(); i < end; ++i)
		{
			int FoundLevelText = BlocksText[i].find("Level");

			if (FoundLevelText != -1)
			{
				break;
			}

			++LineToRemove;
		}

		// Erase lines after level's block
		for (int i = BlocksText.size() - 1; i >= LineToRemove; --i)
		{
			BlocksText.erase(BlocksText.cbegin() + i);
		}

		// Create all blocks
		sf::Vector2f Position;		// Position of each block
		float DeltaY = 60.f;		// Lenght from top edge of screen
		float DeltaX = 140.f;		// Lenght from left edge of screen
		float ScaleFactorY = SETTINGS.GetScaleFactor().Y;
		float ScaleFactorX = SETTINGS.GetScaleFactor().X;
		
		for (int i = 0, endBlocks = BlocksText.size(); i < endBlocks; ++i)
		{
			Position.y = (DeltaY * i * ScaleFactorY) + DeltaY * ScaleFactorY;

			for (int j = 0, endString = BlocksText[i].size(); j < endString; ++j)
			{
				Position.x = (DeltaX * j * ScaleFactorX) + DeltaX / 2.f * ScaleFactorX;

				if (BlocksText[i][j] == '0')
				{
					Blocks.emplace_back(BlockFactories[2]->CreateBlock(Position));
				}
				else if (BlocksText[i][j] == '1')
				{
					Blocks.emplace_back(BlockFactories[0]->CreateBlock(Position));
					++BreakableBlocks;
				}
				else if (BlocksText[i][j] == '2')
				{
					Blocks.emplace_back(BlockFactories[1]->CreateBlock(Position));
					++BreakableBlocks;
				}
			}
		}

		// Create a ball and platform
		Position.x = SETTINGS.GetScreenWidth() / 2.f;
		Position.y = SETTINGS.GetScreenHeight();
		GameObjects.emplace_back(std::make_shared<UPlatform>(Position));

		Position.y = SETTINGS.GetScreenHeight() - GameObjects[0]->GetHeight() * 1.1f;
		GameObjects.emplace_back(std::make_shared<UBall>(Position));
	}

	int ULevelLoader::GetCurrentLevel() const
	{
		return CurrentLevel;
	}

	int ULevelLoader::GetBreackableBlocksCount() const
	{
		return BreakableBlocks;
	}

	const std::vector<std::shared_ptr<IGameObject>>& ULevelLoader::GetGameObjects()
	{
		return GameObjects;
	}

	const std::vector<std::shared_ptr<UBlock>>& ULevelLoader::GetBlocks()
	{
		return Blocks;
	}
}