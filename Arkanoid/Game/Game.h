#pragma once

#include <SFML/Graphics.hpp>
#include "AppStates/AppStates.h"

namespace Arkanoid 
{
	class IGameState;

	class UGame
	{
	public:
		UGame();
		~UGame();
		
		void EventUpdate(const sf::Event& Event);
		void GameplayUpdate(const float DeltaTime);
		void Draw(sf::RenderWindow& Window);

	private:
		// Work tools
		void InitGameState(EGameStateType State);

	private:
		EGameStateType CurrentGameStateType = EGameStateType::MainMenu;	// Game state type which plays now
		std::shared_ptr<IGameState> GameState;							// Game state object to play
	};
}
