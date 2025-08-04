#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../IGameState.h"
#include "../GameStateSubject.h"
#include "../GameStateObserver.h"
#include "../CButton.h"

namespace SettingsMenu
{
	enum class EGameStateType : int
	{
		MainMenu = 0,
	};

	// Types of a settings menu
	enum class ESettingsType : int
	{
		Main = 0,	// Main settings
		Sounds,		// Sound settings
		Video,		// Video settings
	};
}

namespace Arkanoid
{
	class SSettingsMenu final : public IGameState, public IGameStateSubject, public IGameStateObserver,
								public std::enable_shared_from_this<SSettingsMenu>
	{
	public:
		SSettingsMenu() = default;
		~SSettingsMenu() = default;

		// IGameState methods
		void Init() override;
		void EventUpdate(const sf::Event& Event) override;
		void GameplayUpdate(const float DeltaTime) override;
		void Draw(sf::RenderWindow& Window) override;

		// IGameStateSubject methods
		void Attach(std::weak_ptr<IGameStateObserver> Observer) override;
		void Detach(std::weak_ptr<IGameStateObserver> Observer) override;
		void Notify(int NewGameStateType) override;

	private:
		// IGameStateObserver methods
		void GameStateChanged(int NewGameStateType) override;

		// Work tools
		void MoveUp();
		void MoveDown();
		void SetNewGameState(SettingsMenu::EGameStateType NewState);
		void InitSubSettingsMenu(SettingsMenu::ESettingsType Type);

	private:
		std::shared_ptr<IGameState> SubMenu;				// Sub settings menu

		int TitleTextSize = 60;								// Menu title text size
		int ButtonsTextSize = 40;							// Menu buttons text size
		int SelectedButton = 0;								// Index of a selected button

		SettingsMenu::ESettingsType SettingsType;			// Current settings type which shows

		std::vector<sf::Text> Buttons;						// Vector of all clickable buttons 
		sf::Text MenuTitle;									// Menu title

		sf::Texture BackgroundTexture;						// Texture for background
		sf::Sprite BackgroundSprite;						// Sprite which shows on a background
		sf::SoundBuffer MovesSound;							// Sound of menu moves
		sf::SoundBuffer ChoiceSound;						// Sound of menu choices

		CButton Button;										// Keys to work with menu

		std::vector<std::weak_ptr<IGameStateObserver>> Observers;	// Observers of a state
	};
}
