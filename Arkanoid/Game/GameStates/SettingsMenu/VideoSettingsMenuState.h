#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../IGameState.h"
#include "../GameStateSubject.h"
#include "../CButton.h"

namespace VideoSettingMenu
{
	// Types of a settings menu
	enum class ESettingsType : int
	{
		Main = 0,	// Main settings
	};

	// Types of a GUI changes
	enum class EVGUIType : int
	{
		FullscreenMode = 0,
		Resolution,
	};
}

namespace Arkanoid
{
	class STResolutionSettingsMenu;

	class SVideoSettingMenu final : public IGameState, public IGameStateSubject
	{
	public:
		SVideoSettingMenu() = default;
		~SVideoSettingMenu() = default;

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
		// Work tools
		void MoveUp();
		void MoveDown();
		void UpdateUi(VideoSettingMenu::EVGUIType ChangedType);
		void ChangeSettingsType(VideoSettingMenu::ESettingsType NewType);

	private:
		int TitleTextSize = 60;								// Menu title text size
		int ButtonsTextSize = 40;							// Menu buttons text size
		int SelectedButton = 0;								// Index of a selected button
		int ScreenWidth = 0;								// Screen width
		int ScreenHeight = 0;								// Screen height

		bool bIsFullscreenOn = false;						// Flag which contains informaion is fullscreen mode on
		bool bIsResolutionsSnow = false;					// Flag which contains are resolution variables showing
		bool bIsFullscreenModeChanged = false;				// Flag which contains informaion is fullscreen mode changed
		bool bIsResolutionChanged = false;					// Flag which contains information is resolution changed
		
		std::vector<sf::Text> Buttons;						// Vector of all clickable buttons 
		sf::Text MenuTitle;									// Menu title

		sf::SoundBuffer MovesSound;							// Sound of menu moves
		sf::SoundBuffer ChoiceSound;						// Sound of menu choices

		CButton Button;										// Keys to work with menu
		std::shared_ptr<STResolutionSettingsMenu> Resolution;// Class which contains resolution's variables

		std::vector<std::weak_ptr<IGameStateObserver>> Observers;	// Observers of a state
	};
}
