#pragma once

#include <SFML/Graphics.hpp>

namespace Arkanoid
{
	// Types of a settings menu
	enum class ESettingsType : int
	{
		Main = 0,	// Main settings
		Sounds,		// Sound settings
		Video,		// Video settings
	};

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