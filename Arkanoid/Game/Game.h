#pragma once

#include <SFML/Graphics.hpp>
#include "AppStates/AppStates.h"

namespace Arkanoid 
{
	class IGameState;
	class IGameObject;

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
		EGameStateType CurrentGameStateType = EGameStateType::MainMenu;
		std::shared_ptr<IGameState> GameState;
		std::vector<std::shared_ptr<IGameObject>> GameObjects;
	};
}
