#include <cassert>
#include "GameManager.h"
#include "../../../Settings/Settings.h"

namespace Arkanoid
{
	/*//////////////////////////////////*/
	/*                                  */
	/*			  OGAMESTATE		    */
	/*                                  */
	/*//////////////////////////////////*/

	OGameState::OGameState()
	{
		GameState = std::make_shared<CGameState>();
	}

	void OGameState::SaveGameState(std::shared_ptr<CGameState> GameState, int BlocksCount, int PlayerScore)
	{
		this->GameState = GameState;
		this->BlocksCount = BlocksCount;
		this->PlayerScore = PlayerScore;
	}

	std::shared_ptr<CGameState> OGameState::GetGameState() 
	{
		return GameState;
	}

	int OGameState::GetBlocksCount() const
	{
		return BlocksCount;
	}

	int OGameState::GetPlayerScore() const
	{
		return PlayerScore;
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*			OGAMEMANAGER            */
	/*                                  */
	/*//////////////////////////////////*/

	OGameManager::OGameManager(int BreakableBlocks, int BallLifes)
		: BlocksCount(BreakableBlocks)
		, BallLifesCount(BallLifes)
	{
		bool bIsLoaded = WinSound.loadFromFile("Resources/Sounds/AppleEat.wav");
		assert(bIsLoaded);

		bIsLoaded = LoseSound.loadFromFile("Resources/Sounds/Maodin204__Lose.wav");
		assert(bIsLoaded);

		GameState = std::make_shared<OGameState>();
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

	void OGameManager::SaveGameState(std::shared_ptr<CGameState> NewGameState)
	{
		GameState->SaveGameState(NewGameState, BlocksCount, PlayerScore);
	}

	std::shared_ptr<CGameState> OGameManager::GetGameState()
	{
		BlocksCount = GameState->GetBlocksCount();
		PlayerScore = GameState->GetPlayerScore();

		return GameState->GetGameState();
	}

	// Set Gameplay type by default
	void OGameManager::ClearGameplayType()
	{
		bIsGameplayTypeChanged = false;
		CurrentGameplayType = EGameplayType::Main;
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