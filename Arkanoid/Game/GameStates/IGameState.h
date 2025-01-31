#pragma once

#include <SFML/Graphics.hpp>

namespace Arkanoid
{
	class IGameState
	{
	public:
		virtual ~IGameState() = default;

		virtual void Init() = 0;
		virtual void EventUpdate(const sf::Event& Event) = 0;
		virtual void GameplayUpdate(const float DeltaTime) = 0;
		virtual void Draw(sf::RenderWindow& Window) = 0;
	};
}