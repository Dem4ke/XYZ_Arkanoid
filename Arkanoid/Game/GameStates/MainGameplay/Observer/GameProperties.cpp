#include <cassert>
#include "GameProperties.h"


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
	/*		 UGAMEPROPERTIES            */
	/*                                  */
	/*//////////////////////////////////*/

	UGameProperties::UGameProperties()
	{
		GameState = std::make_shared<OGameState>();
	}

	void UGameProperties::DeleteBlock()
	{
		--BlocksCount;
	}

	void UGameProperties::SetBlocksCount(int Value)
	{
		BlocksCount = Value;
	}

	int UGameProperties::GetBlocksCount() const
	{
		return BlocksCount;
	}

	void UGameProperties::DecreaseBallLife()
	{
		--BallLifesCount;
	}

	void UGameProperties::SetBallLifes(int Value)
	{
		BallLifesCount = Value;
	}

	int UGameProperties::GetBallLifes() const 
	{
		return BallLifesCount;
	}

	void UGameProperties::IncreasePlayerScore(int Value)
	{
		PlayerScore += Value;
	}

	void UGameProperties::SetPlayerScore(int Value)
	{
		PlayerScore = Value;
	}

	int UGameProperties::GetPlayerScore() const
	{
		return PlayerScore;
	}

	void UGameProperties::SetGameState(std::shared_ptr<CGameState> NewGameState)
	{
		GameState->SaveGameState(NewGameState, BlocksCount, PlayerScore);
	}

	std::shared_ptr<CGameState> UGameProperties::GetGameState()
	{
		PlayerScore = GameState->GetPlayerScore();
		BlocksCount = GameState->GetBlocksCount();
		return GameState->GetGameState();
	}

	//OGameManager::OGameManager(int BreakableBlocks, int BallLifes)
	//	: BlocksCount(BreakableBlocks)
	//	, BallLifesCount(BallLifes)
	//{
	//	bool bIsLoaded = WinSound.loadFromFile("Resources/Sounds/AppleEat.wav");
	//	assert(bIsLoaded);

	//	bIsLoaded = LoseSound.loadFromFile("Resources/Sounds/Maodin204__Lose.wav");
	//	assert(bIsLoaded);

	//	UI = std::make_shared<OGameUI>();
	//	GameState = std::make_shared<OGameState>();

	//	UI->SetScore(PlayerScore);
	//	UI->SetBallLifes(BallLifesCount);
	//}

	//void OGameManager::BlockBroken(int Cost, const sf::Vector2f& Position)
	//{
	//	--BlocksCount;
	//	PlayerScore += Cost;
	//	UI->SetScore(PlayerScore);

	//	if (BlocksCount <= 0)
	//	{
	//		ChangeGameplayType(EGameplayType::LevelDone);
	//	}
	//}

	//void OGameManager::BallOut()
	//{
	//	--BallLifesCount;
	//	UI->SetBallLifes(BallLifesCount);

	//	if (BallLifesCount <= 0)
	//	{
	//		ChangeGameplayType(EGameplayType::GameOver);
	//	}
	//	else
	//	{
	//		ChangeGameplayType(EGameplayType::RecreateBall);
	//	}
	//}

	//void OGameManager::SaveGameState(std::shared_ptr<CGameState> NewGameState)
	//{
	//	GameState->SaveGameState(NewGameState, BlocksCount, PlayerScore);
	//}

	//std::shared_ptr<CGameState> OGameManager::GetGameState()
	//{
	//	BlocksCount = GameState->GetBlocksCount();
	//	PlayerScore = GameState->GetPlayerScore();
	//	UI->SetScore(PlayerScore);

	//	return GameState->GetGameState();
	//}

	//// Set Gameplay type by default
	//void OGameManager::ClearGameplayType()
	//{
	//	bIsGameplayTypeChanged = false;
	//	CurrentGameplayType = EGameplayType::Main;
	//}

	//bool OGameManager::IsGameplayTypeChanged() const
	//{
	//	return bIsGameplayTypeChanged;
	//}

	//EGameplayType OGameManager::GetGameplayType() const
	//{
	//	return CurrentGameplayType;
	//}

	//void OGameManager::DrawUI(sf::RenderWindow& Window)
	//{
	//	UI->Draw(Window);
	//}

	//void OGameManager::ChangeGameplayType(EGameplayType NewType)
	//{
	//	bIsGameplayTypeChanged = true;
	//	CurrentGameplayType = NewType;

	//	switch (CurrentGameplayType)
	//	{
	//	case EGameplayType::LevelDone:
	//	{
	//		SETTINGS.GetResources()->PlaySound(WinSound);
	//		break;
	//	}
	//	case EGameplayType::GameOver:
	//	{
	//		SETTINGS.GetResources()->PlaySound(LoseSound);
	//		break;
	//	}
	//	}
	//}
}