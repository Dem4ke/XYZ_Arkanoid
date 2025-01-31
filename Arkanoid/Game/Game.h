#pragma once
#include <SFML/Graphics.hpp>

namespace Arkanoid 
{
	class IGameState;
	class IGameObject;

	class UGame
	{
	public:
		UGame();
		
		void EventUpdate(const sf::Event& Event);
		void GameplayUpdate(const float DeltaTime, sf::RenderWindow& Window);

	private:
		std::shared_ptr<IGameState> GameState;
		std::vector<std::shared_ptr<IGameObject>> GameObjects;
	};
}
