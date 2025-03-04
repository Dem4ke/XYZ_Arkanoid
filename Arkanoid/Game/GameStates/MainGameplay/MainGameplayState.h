#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../IGameState.h"
#include "../CButton.h"

namespace Arkanoid
{
	class ISubGameplayState;
	class IGameObject;
	class ULevelLoader;
	class OGameManager;
	class UBlock;

	class SMainGameplay final : public IGameState
	{
	public:
		SMainGameplay();
		~SMainGameplay() = default;

		void EventUpdate(const sf::Event& Event) override;
		void GameplayUpdate(const float DeltaTime) override;
		void Draw(sf::RenderWindow& Window) override;

		bool IsGameStateUpdated() const override;
		EGameStateType GetNewGameStateType() const override;

	private:
		// Work tools
		void InitNewLevel();
		void RecreateBall();
		void SetNewGameState(EGameStateType NewState);
		void InitSubGameplayState(EGameplayType Type);

	private:
		std::shared_ptr<ISubGameplayState> SubGameplayState;	// Sub gameplay menus (pause dialog and other)
		std::shared_ptr<ULevelLoader> LevelLoader;				// Class to load levels from config file
		std::shared_ptr<OGameManager> Observer;					// Game observer to the blocks and ball

		std::vector<std::shared_ptr<IGameObject>> GameObjects;	// Vector of playable objects (ball, platform)
		std::vector<std::shared_ptr<UBlock>> Blocks;			// Vector of blocks
		

		bool bIsGameStateUpdated = false;						// Flag contains iformaion is user changed a game state type
		EGameStateType NewGameStateType = EGameStateType::None; // Next game state type that will be played
		EGameplayType GameplayType = EGameplayType::Main;		// Current gameplay type which shows

		sf::Texture BackgroundTexture;							// Texture for background
		sf::Sprite BackgroundSprite;							// Sprite which shows on a background
		sf::SoundBuffer MovesSound;								// Sound of menu moves
		sf::SoundBuffer ChoiceSound;							// Sound of menu choices

		CButton Button;											// Keys to work with game
	};
}
