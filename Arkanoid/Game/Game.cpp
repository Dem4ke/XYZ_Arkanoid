#include "Game.h"
#include "GameStates/MainGameplay/MainGameplayState.h"
#include "GameStates/MainMenu/MainMenuState.h"
#include "GameStates/SettingsMenu/SettingsMenuState.h"
#include "GameStates/LeaderBoardMenu/LeaderBoardMenuState.h"
#include "GameStates/ExitMenu/ExitMenuState.h"

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
		}
		else
		{
			InitGameState(CurrentGameStateType);
		}

		GameState->EventUpdate(Event);
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
		}
		else
		{
			InitGameState(CurrentGameStateType);
		}

		GameState->GameplayUpdate(DeltaTime);
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
		if (GameState) 
		{
			GameState = nullptr;
		}

		switch (State) 
		{
		case EGameStateType::MainMenu:
		{
			GameState = std::make_shared<SMainMenu>();
			break;
		}
		case EGameStateType::SettingsMenu:
		{
			GameState = std::make_shared<SSettingsMenu>();
			break;
		}
		case EGameStateType::LeaderBoardMenu:
		{
			GameState = std::make_shared<SLeaderBoardMenu>(); 
			break;
		}
		case EGameStateType::ExitMenu:
		{
			GameState = std::make_shared<SExitMenu>();
			break;
		}
		case EGameStateType::MainGameplay:
		{
			GameState = std::make_shared<SMainGameplay>();
			break;
		}
		}

		GameState->Init();
	}
}