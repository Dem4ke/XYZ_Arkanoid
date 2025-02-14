#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../CButton.h"

namespace Arkanoid
{
	class STResolutionSettingsMenu
	{
	public:
		STResolutionSettingsMenu();
		~STResolutionSettingsMenu() = default;

		void EventUpdate(const sf::Event& Event);
		void Draw(sf::RenderWindow& Window);

		int GetWidth() const;
		int GetHeight() const;

		bool IsExit() const;
		bool IsChosen() const;

	private:
		// Work tools
		void MoveUp();
		void MoveDown();

	private:
		int ButtonsTextSize = 40;							// Menu buttons text size
		int SelectedButton = 0;								// Index of a selected button

		int ScreenWidth = 0;								// Screen width
		int ScreenHeight = 0;								// Screen height

		bool bIsExit = false;								// Flag contains is user exit from menu
		bool bIsChosen = false;								// Flag contains is user choose resolution

		std::vector<sf::Text> Buttons;						// Vector of all clickable buttons 

		sf::SoundBuffer MovesSound;							// Sound of menu moves
		sf::SoundBuffer ChoiceSound;						// Sound of menu choices

		CButton Button;										// Keys to work with menu
	};
}
