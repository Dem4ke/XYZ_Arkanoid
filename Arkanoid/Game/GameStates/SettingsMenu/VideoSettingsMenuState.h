#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ISubSettingsMenuState.h"
#include "../CButton.h"

namespace Arkanoid
{
	struct CResolution;

	// What type of GUI has changed
	enum class EGUIType : int
	{
		FullscreenMode = 0,
		Resolution,
	};

	class STVideoSettingMenu final : public ISubSettingsMenu
	{
	public:
		STVideoSettingMenu();
		~STVideoSettingMenu() = default;

		void EventUpdate(const sf::Event& Event) override;
		void Draw(sf::RenderWindow& Window) override;

		bool IsSettingsTypeChanged() const override;
		ESettingsType GetNewSettingsType() const override;

	private:
		// Work tools
		void MoveUp();
		void MoveDown();
		void UpdateUi(EGUIType ChangedType);
		void ChangeSettingsType(ESettingsType NewType);

	private:
		int TitleTextSize = 60;								// Menu title text size
		int ButtonsTextSize = 40;							// Menu buttons text size
		int SelectedButton = 0;								// Index of a selected button
		int ScreenWidth = 0;								// Screen width
		int ScreenHeight = 0;								// Screen height

		bool bIsFullscreenOn = false;						// Flag which contains informaion is fullscreen mode on
		bool bIsResolutionsSnow = false;					// Flag which contains are resolution variables showing
		bool bIsSettingsTypeUpdated = false;				// Flag contains informaion is user changed a settings type
		ESettingsType SettingsType = ESettingsType::Video;	// Current settings type which shows

		std::vector<sf::Text> Buttons;						// Vector of all clickable buttons 
		sf::Text MenuTitle;									// Menu title

		sf::Color CommonButtonColor = sf::Color::White;		// Color of all unchosen buttons
		sf::Color ChosenButtonColor = sf::Color::Blue;		// Color of a selected button

		sf::SoundBuffer MovesSound;							// Sound of menu moves
		sf::SoundBuffer ChoiceSound;						// Sound of menu choices

		CButton Button;										// Keys to work with menu
		std::shared_ptr<CResolution> Resolution;			// Struct which contains resolution's variables
	};
}
