#pragma once

#include <SFML/Graphics.hpp>
#include "../AppStates/AppStates.h"

namespace Arkanoid
{
	class IGameState
	{
	public:
		virtual ~IGameState() = default;
		virtual void EventUpdate(const sf::Event& Event) = 0;
		virtual void GameplayUpdate(const float DeltaTime) = 0;
		virtual void Draw(sf::RenderWindow& Window) = 0;
		 
		virtual bool IsGameStateUpdated() const = 0;
		virtual EGameStateType GetNewGameStateType() const = 0;
	};
}