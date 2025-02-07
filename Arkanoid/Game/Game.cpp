#include "Game.h"
#include "GameStates/MainMenu/MainMenuState.h"

namespace Arkanoid
{
	UGame::UGame() 
	{
		// Initialization of main menu state
		InitGameState(CurrentGameStateType);
	}

	UGame::~UGame() {}

	void UGame::EventUpdate(const sf::Event& Event)
	{
		if (GameState)
		{
			if (GameState->IsGameStateUpdated())
			{
				CurrentGameStateType = GameState->GetNewGameStateType();
				InitGameState(CurrentGameStateType);
			}

			GameState->EventUpdate(Event);
		}
		else
		{
			InitGameState(CurrentGameStateType);
		}
	}

	void UGame::GameplayUpdate(const float DeltaTime)
	{
		if (GameState)
		{
			if (GameState->IsGameStateUpdated())
			{
				CurrentGameStateType = GameState->GetNewGameStateType();
				InitGameState(CurrentGameStateType);
			}

			GameState->GameplayUpdate(DeltaTime);
		}
		else
		{
			InitGameState(CurrentGameStateType);
		}
	}

	void UGame::Draw(sf::RenderWindow& Window)
	{
		if (GameState)
		{
			GameState->Draw(Window);
		}
		else
		{
			InitGameState(CurrentGameStateType);
		}
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	      PRIVATE WORKTOOLS         */
	/*                                  */
	/*//////////////////////////////////*/

	void UGame::InitGameState(EGameStateType State)
	{
		switch (State) 
		{
		case EGameStateType::MainMenu:
		{
			GameState = std::make_shared<SMainMenu>();
		}
		case EGameStateType::SettingsMenu:
		{
			GameState = std::make_shared<SMainMenu>();
		}
		case EGameStateType::LeaderBoardMenu:
		{
			GameState = std::make_shared<SMainMenu>();
		}
		case EGameStateType::ExitMenu:
		{
			GameState = std::make_shared<SMainMenu>();
		}
		case EGameStateType::MainGameplay:
		{
			GameState = std::make_shared<SMainMenu>();
		}
		}
	}
}