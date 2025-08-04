#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../IGameState.h"
#include "../GameStateSubject.h"
#include "../CButton.h"

namespace SoundSettingsMenu
{
	// Types of a settings menu
	enum class ESettingsType : int
	{
		Main = 0,	// Main settings
	};

	// Types of a GUI changes
	enum class ESGUIType : int
	{
		Sounds = 0,
		Music,
	};
}

namespace Arkanoid
{
	class SSoundSettingsMenu final : public IGameState, public IGameStateSubject
	{
	public:
		SSoundSettingsMenu() = default;
		~SSoundSettingsMenu() = default;

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
		void UpdateUi(SoundSettingsMenu::ESGUIType ChangedType);
		void ChangeSettingsType(SoundSettingsMenu::ESettingsType NewType);

	private:
		int TitleTextSize = 60;								// Menu title text size
		int ButtonsTextSize = 40;							// Menu buttons text size
		int SelectedButton = 0;								// Index of a selected button

		bool bIsSoundsOn = true;							// Flag which contains informaion is sounds on
		bool bIsMusicOn = true;								// Flag which contains informaion is music on

		std::vector<sf::Text> Buttons;						// Vector of all clickable buttons 
		sf::Text MenuTitle;									// Menu title

		sf::SoundBuffer MovesSound;							// Sound of menu moves
		sf::SoundBuffer ChoiceSound;						// Sound of menu choices

		CButton Button;										// Keys to work with menu

		std::vector<std::weak_ptr<IGameStateObserver>> Observers;	// Observers of a state
	};
}
