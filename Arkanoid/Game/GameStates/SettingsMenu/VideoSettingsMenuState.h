#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../IGameState.h"
#include "../CButton.h"

namespace Arkanoid
{
	class STVideoSettingMenu
	{
	public:
		STVideoSettingMenu();
		~STVideoSettingMenu() = default;

		void EventUpdate(const sf::Event& Event);
		void Draw(sf::RenderWindow& Window);

		bool IsSettingsTypeChanged() const;
		ESettingsType GetNewSettingsType() const;

	private:
		// Work tools
		void MoveUp();
		void MoveDown();
		void ChangeSettingsType(ESettingsType NewType);

	private:
		int TitleTextSize = 60;								// Menu title text size
		int ButtonsTextSize = 40;							// Menu buttons text size
		int SelectedButton = 0;								// Index of a selected button

		bool bIsSettingsTypeUpdated = false;				// Flag contains iformaion is user changed a settings type
		ESettingsType SettingsType = ESettingsType::Video;	// Current settings type which shows

		std::vector<sf::Text> Buttons;						// Vector of all clickable buttons 
		sf::Text MenuTitle;									// Menu title

		sf::Color CommonButtonColor = sf::Color::White;		// Color of all unchosen buttons
		sf::Color ChosenButtonColor = sf::Color::Blue;		// Color of a selected button

		sf::SoundBuffer MovesSound;							// Sound of menu moves
		sf::SoundBuffer ChoiceSound;						// Sound of menu choices

		CButton Button;										// Keys to work with menu
	};
}
