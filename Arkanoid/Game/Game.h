#pragma once

#include "GameStates/GameStateObserver.h"

namespace Arkanoid 
{
	class OGameStatesManager;

	class UGame final : public IGameStateObserver,
		public std::enable_shared_from_this<UGame>
	{
	public:
		UGame() = default;
		~UGame() = default;
		
		void Init();

		void EventUpdate(const sf::Event& Event);
		void GameplayUpdate(const float DeltaTime);
		void Draw(sf::RenderWindow& Window);

	private:
		void GameStateChanged(int NewGameStateType) override;

		std::shared_ptr<IGameState> GameState = nullptr;	// Current game state
	};
}
