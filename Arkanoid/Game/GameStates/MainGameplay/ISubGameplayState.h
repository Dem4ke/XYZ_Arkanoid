#pragma once

#include <SFML/Graphics.hpp>
#include "../../AppStates/AppStates.h"

namespace Arkanoid
{
	class ISubGameplayState
	{
	public:
		virtual ~ISubGameplayState() = default;
		virtual void EventUpdate(const sf::Event& Event) = 0;
		virtual void Draw(sf::RenderWindow& Window) = 0;
		
		virtual bool IsGameplayTypeChanged() const = 0;
		virtual EGameplayType GetNewGameplayType() const = 0;
	};
}