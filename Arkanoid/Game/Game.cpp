#include "Game.h"
#include "GameStates/MainGameplay/MainGameplayState.h"
#include "GameStates/MainMenu/MainMenuState.h"
#include "GameStates/SettingsMenu/SettingsMenuState.h"
#include "GameStates/LeaderBoardMenu/LeaderBoardMenuState.h"
#include "GameStates/ExitMenu/ExitMenuState.h"
#include "GameStates/GameStateSubject.h"

namespace Arkanoid
{
	void UGame::Init()
	{
		// Initialization of main menu state
		GameStateChanged(0);
	}

	void UGame::EventUpdate(const sf::Event& Event)
	{
		if (GameState)
		{
			GameState->EventUpdate(Event);
		}
	}

	void UGame::GameplayUpdate(const float DeltaTime)
	{
		if (GameState)
		{
			GameState->GameplayUpdate(DeltaTime);
		}
	}

	void UGame::Draw(sf::RenderWindow& Window)
	{
		if (GameState)
		{
			GameState->Draw(Window);
		}
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	      PRIVATE WORKTOOLS         */
	/*                                  */
	/*//////////////////////////////////*/

	void UGame::GameStateChanged(int NewGameStateType)
	{
		if (GameState)
		{
			GameState = nullptr;
		}

		switch (NewGameStateType)
		{
		case 0:
		{
			GameState = std::make_shared<SMainMenu>();
			break;
		}
		case 1:
		{
			GameState = std::make_shared<SMainGameplay>();
			break;
		}
		case 2:
		{
			GameState = std::make_shared<SLeaderBoardMenu>();
			break;
		}
		case 3:
		{
			GameState = std::make_shared<SSettingsMenu>();
			break;
		}
		case 4:
		{
			GameState = std::make_shared<SExitMenu>();
			break;
		}
		}

		GameState->Init();

		// Add observer to game state
		std::shared_ptr<IGameStateSubject> GameStateSubject = std::dynamic_pointer_cast<IGameStateSubject>(GameState);
		GameStateSubject->Attach(weak_from_this());
	}
}