#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../IGameState.h"
#include "../GameStateSubject.h"
#include "../CButton.h"

namespace ExitMenu
{
	enum class EGameStateType : int
	{
		MainMenu = 0,
	};
}

namespace Arkanoid
{
	class SExitMenu final : public IGameState, public IGameStateSubject
	{
	public:
		SExitMenu() = default;
		~SExitMenu() = default;

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
		void SetNewGameState(ExitMenu::EGameStateType NewState);

	private:
		int TitleTextSize = 60;								// Menu title text size
		int ButtonsTextSize = 40;							// Menu buttons text size
		int SelectedButton = 0;								// Index of a selected button

		bool bIsExit = false;								// Flag contains information is user want to exit
		
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