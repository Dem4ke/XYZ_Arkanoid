#pragma once

#include "IGameObject.h"

namespace Arkanoid
{
	class ULevelLoader final
	{
	public:
		ULevelLoader();
		~ULevelLoader() = default;

		void Load(int LevelIndex);

		std::vector

	private:
		std::vector<std::shared_ptr<IGameObject>> GameObjects;	// Vector of playable objects (ball, platform)
		std::vector<std::shared_ptr<IGameObject>> Blocks;		// Vector of blocks
	};
}