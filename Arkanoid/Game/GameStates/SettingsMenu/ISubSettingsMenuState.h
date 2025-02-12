#pragma once

#include <SFML/Graphics.hpp>
#include "../../AppStates/AppStates.h"

namespace Arkanoid
{
	class ISubSettingsMenu
	{
	public:
		virtual ~ISubSettingsMenu() = default;
		virtual void EventUpdate(const sf::Event& Event) = 0;
		virtual void Draw(sf::RenderWindow& Window) = 0;
		
		virtual bool IsSettingsTypeChanged() const = 0;
		virtual ESettingsType GetNewSettingsType() const = 0;
	};
}