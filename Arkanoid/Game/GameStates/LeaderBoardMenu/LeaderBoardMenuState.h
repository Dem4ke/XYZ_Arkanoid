#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../IGameState.h"
#include "../CButton.h"

namespace Arkanoid
{
	class SLeaderBoardMenu final : public IGameState
	{
	public:
		SLeaderBoardMenu();
		~SLeaderBoardMenu() = default;

		void Init() override;
		void EventUpdate(const sf::Event& Event) override;
		void GameplayUpdate(const float DeltaTime) override;
		void Draw(sf::RenderWindow& Window) override;

		bool IsGameStateUpdated() const override;
		EGameStateType GetNewGameStateType() const override;

	private:
		// Work tools
		void SetNewGameState(EGameStateType NewState);

	private:
		int TitleTextSize = 60;								// Menu title text size
		int ButtonsTextSize = 40;							// Menu buttons text size
		int DrawablePlayers = 10;							// Count of drawable positions of players in the table

		bool bIsGameStateUpdated = false;					// Flag contains iformaion is user changed a game state type
		EGameStateType NewGameStateType = EGameStateType::None; // Next game state type that will be played

		std::vector<std::pair<sf::Text, sf::Text>> Table;	// Vector of visible players in leader board
		sf::Text ExitButton;								// Exit button
		sf::Text MenuTitle;									// Menu title

		sf::Texture BackgroundTexture;						// Texture for background
		sf::Sprite BackgroundSprite;						// Sprite which shows on a background
		sf::SoundBuffer MovesSound;							// Sound of menu moves
		sf::SoundBuffer ChoiceSound;						// Sound of menu choices

		CButton Button;										// Keys to work with menu
	};
}