#include <cassert>
#include "GameManager.h"
#include "../../../Settings/Settings.h"

namespace Arkanoid
{
	OGameManager::OGameManager(int BreakableBlocks, int BallLifes)
		: BlocksCount(BreakableBlocks)
		, BallLifesCount(BallLifes)
	{
		bool bIsLoaded = WinSound.loadFromFile("Resources/Sounds/AppleEat.wav");
		assert(bIsLoaded);

		bIsLoaded = LoseSound.loadFromFile("Resources/Sounds/Maodin204__Lose.wav");
		assert(bIsLoaded);
	}

	void OGameManager::BlockBroken(int Cost)
	{
		--BlocksCount;
		PlayerScore += Cost;

		if (BlocksCount <= 0)
		{
			ChangeGameplayType(EGameplayType::LevelDone);
		}
	}
	void OGameManager::BallOut()
	{
		--BallLifesCount;

		if (BallLifesCount <= 0)
		{
			ChangeGameplayType(EGameplayType::GameOver);
		}
		else
		{
			ChangeGameplayType(EGameplayType::RecreateBall);
		}
	}

	bool OGameManager::IsGameplayTypeChanged() const
	{
		return bIsGameplayTypeChanged;
	}

	EGameplayType OGameManager::GetGameplayType() const
	{
		return CurrentGameplayType;
	}

	void OGameManager::ChangeGameplayType(EGameplayType NewType)
	{
		bIsGameplayTypeChanged = true;
		CurrentGameplayType = NewType;

		switch (CurrentGameplayType)
		{
		case EGameplayType::LevelDone:
		{
			SETTINGS.GetResources()->PlaySound(WinSound);
			break;
		}
		case EGameplayType::GameOver:
		{
			SETTINGS.GetResources()->PlaySound(LoseSound);
			break;
		}
		}
	}
}