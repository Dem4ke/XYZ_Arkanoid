#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../IGameState.h"
#include "../GameStateSubject.h"
#include "../CButton.h"

namespace MainMenu 
{
	enum class EGameStateType : int
	{
		MainGameplay = 1,
		LeaderBoardMenu = 2,
		SettingsMenu = 3,
		ExitMenu = 4,
	};
}

namespace Arkanoid
{
	class SMainMenu final : public IGameState, public IGameStateSubject
	{
	public:
		SMainMenu() = default;
		~SMainMenu() = default;

		void Init() override;
		void EventUpdate(const sf::Event& Event) override;
		void GameplayUpdate(const float DeltaTime) override;
		void Draw(sf::RenderWindow& Window) override;

		void Attach(std::weak_ptr<IGameStateObserver> Observer) override;
		void Detach(std::weak_ptr<IGameStateObserver> Observer) override;
		void Notify(int NewGameStateType) override;

	private:
		// Work tools
		void MoveUp();
		void MoveDown();
		void SetNewGameState(MainMenu::EGameStateType NewState);

	private:
		int TitleTextSize = 60;								// Menu title text size
		int ButtonsTextSize = 40;							// Menu buttons text size
		int SelectedButton = 0;								// Index of a selected button
		
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