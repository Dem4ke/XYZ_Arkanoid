#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../ISubGameplayState.h"
#include "../../CButton.h"

namespace Arkanoid
{
	class PauseState final : public ISubGameplayState
	{
	public:
		PauseState();
		~PauseState() = default;

		void EventUpdate(const sf::Event& Event) override;
		void Draw(sf::RenderWindow& Window) override;
		
		bool IsGameplayTypeChanged() const override;
		EGameplayType GetNewGameplayType() const override;

	private:
		// Work tools
		void MoveUp();
		void MoveDown();
		void ChangeGameplayType(EGameplayType NewType);

	private:
		int TitleTextSize = 60;								// Menu title text size
		int ButtonsTextSize = 40;							// Menu buttons text size
		int SelectedButton = 0;								// Index of a selected button

		bool bIsSettingsTypeUpdated = false;				// Flag which contains informaion is user changed a settings type
		ESettingsType SettingsType = ESettingsType::Sounds;	// Current settings type which shows

		std::vector<sf::Text> Buttons;						// Vector of all clickable buttons 
		sf::Text MenuTitle;									// Menu title

		sf::SoundBuffer MovesSound;							// Sound of menu moves
		sf::SoundBuffer ChoiceSound;						// Sound of menu choices

		CButton Button;										// Keys to work with menu
	};
}