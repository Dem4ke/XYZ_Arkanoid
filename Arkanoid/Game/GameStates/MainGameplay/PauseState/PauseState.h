#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../../IGameState.h"
#include "../../GameStateSubject.h"
#include "../../CButton.h"

namespace PauseState
{
	enum class EPauseStateType : int
	{
		ExitToMainMenu = 0,
		ContinueGame,
	};
}

namespace Arkanoid
{
	class IGameStateObserver;

	class SPauseState final : public IGameState, public IGameStateSubject
	{
	public:
		SPauseState() = default;
		~SPauseState() = default;

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
		void ChangeGameplayType(PauseState::EPauseStateType NewType);

	private:
		int TitleTextSize = 60;								// Menu title text size
		int ButtonsTextSize = 40;							// Menu buttons text size
		int SelectedButton = 0;								// Index of a selected button

		std::vector<sf::Text> Buttons;						// Vector of all clickable buttons 
		sf::Text MenuTitle;									// Menu title

		sf::SoundBuffer MovesSound;							// Sound of menu moves
		sf::SoundBuffer ChoiceSound;						// Sound of menu choices

		CButton Button;										// Keys to work with menu

		std::vector<std::weak_ptr<IGameStateObserver>> Observers;	// Observers of a state
	};
}