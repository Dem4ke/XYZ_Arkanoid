#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../IGameState.h"
#include "../CButton.h"

namespace Arkanoid
{
	class ISubSettingsMenu;

	class SSettingsMenu final : public IGameState
	{
	public:
		SSettingsMenu();
		~SSettingsMenu() = default;

		void EventUpdate(const sf::Event& Event) override;
		void GameplayUpdate(const float DeltaTime) override;
		void Draw(sf::RenderWindow& Window) override;

		bool IsGameStateUpdated() const override;
		EGameStateType GetNewGameStateType() const override;

	private:
		// Work tools
		void Init();
		void MoveUp();
		void MoveDown();
		void SetNewGameState(EGameStateType NewState);
		void InitSubSettingsMenu(ESettingsType Type);

	private:
		std::shared_ptr<ISubSettingsMenu> SubMenu;			// Sub settings menu

		int TitleTextSize = 60;								// Menu title text size
		int ButtonsTextSize = 40;							// Menu buttons text size
		int SelectedButton = 0;								// Index of a selected button

		bool bIsGameStateUpdated = false;					// Flag contains iformaion is user changed a game state type
		EGameStateType NewGameStateType = EGameStateType::None; // Next game state type that will be played
		ESettingsType SettingsType = ESettingsType::Main;	// Current settings type which shows

		std::vector<sf::Text> Buttons;						// Vector of all clickable buttons 
		sf::Text MenuTitle;									// Menu title

		sf::Texture BackgroundTexture;						// Texture for background
		sf::Sprite BackgroundSprite;						// Sprite which shows on a background
		sf::SoundBuffer MovesSound;							// Sound of menu moves
		sf::SoundBuffer ChoiceSound;						// Sound of menu choices

		CButton Button;										// Keys to work with menu
	};
}
