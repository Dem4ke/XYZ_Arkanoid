#pragma once

#include <SFML/Audio.hpp>
#include "Observer.h"
#include "../../../AppStates/AppStates.h"

namespace Arkanoid
{
	// Observer that subscribes on each block and ball and checks is ball out and how many blocks left
	class OGameManager final : public IBlockObserver, public IBallObserver, public IGameManager
	{
	public:
		OGameManager(int BreakableBlocks, int BallLifes);
		~OGameManager() = default;

		void BlockBroken(int Cost) override;
		void BallOut() override;

		bool IsGameplayTypeChanged() const override;
		EGameplayType GetGameplayType() const override;

	private:
		void ChangeGameplayType(EGameplayType NewType);

		int BlocksCount = 0;	// Count of breakable blocks of the field
		int BallLifesCount = 3;	// Count of ball's lifes
		int PlayerScore = 0;	// How many points player has

		bool bIsGameplayTypeChanged = false;
		EGameplayType CurrentGameplayType = EGameplayType::Main;

		sf::SoundBuffer WinSound;		// Sound of level complete
		sf::SoundBuffer LoseSound;		// Sound of game over
	};
}