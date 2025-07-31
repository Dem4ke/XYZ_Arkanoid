#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../GameStateSubject.h"
#include "Observer/Observer.h"
#include "../IGameState.h"
#include "../CButton.h"

namespace Arkanoid
{
	class ISubGameplayState;
	class IGameObject;
	class ULevelLoader;
	class OBonusManager;
	class UBlock;
	class UBonus;
	class OGameUI;
	class UGameProperties;

	class SMainGameplay final : public IGameState, public IGameStateSubject,
								public IBallObserver, public IBlockObserver, public IBonusObserver, 
		public std::enable_shared_from_this<SMainGameplay>
	{
	public:
		SMainGameplay();
		~SMainGameplay() = default;

		void Init() override;
		void EventUpdate(const sf::Event& Event) override;
		void GameplayUpdate(const float DeltaTime) override;
		void Draw(sf::RenderWindow& Window) override;

		// IBlockObserver methods
		void BlockBroken(int Cost, const sf::Vector2f& Position) override;

		// IBallObserver methods
		void BallOut() override;

		// IBonusObserver methods
		void BonusTaken(int Type) override;

	private:
		// Work tools
		void SaveGameState(std::shared_ptr<CGameState> NewGameState);
		std::shared_ptr<CGameState> GetGameState();

		void InitNewLevel();
		void RecreateBall();
		void SetNewGameState(EGameStateType NewState);
		void InitSubGameplayState(EGameplayType Type);

	private:
		std::shared_ptr<ISubGameplayState> SubGameplayState = nullptr;	// Sub gameplay menus (pause dialog and other)
		std::shared_ptr<ULevelLoader> LevelLoader = nullptr;			// Class to load levels from config file
		std::shared_ptr<UGameProperties> GameProperties = nullptr;		// Game properties
		std::shared_ptr<OGameUI> UI = nullptr;							// User Interface

		std::vector<std::shared_ptr<IGameObject>> GameObjects;			// Vector of playable objects (ball, platform)
		std::vector<std::shared_ptr<UBonus>> Bonuses;					// Vector of bonuses
		std::vector<std::shared_ptr<UBlock>> Blocks;					// Vector of blocks
		
		EGameplayType GameplayType = EGameplayType::Main;				// Current gameplay type which shows

		sf::Texture BackgroundTexture;									// Texture for background
		sf::Sprite BackgroundSprite;									// Sprite which shows on a background
		sf::SoundBuffer MovesSound;										// Sound of menu moves
		sf::SoundBuffer ChoiceSound;									// Sound of menu choices
		sf::SoundBuffer WinSound;										// Sound of a level complete
		sf::SoundBuffer LoseSound;										// Sound of the game over
		sf::SoundBuffer HitSound;										// Sound of ball or bonus hit
			
		CButton Button;													// Keys to work with game

		std::vector<std::weak_ptr<IGameStateObserver>> Observers;	// Observers of a state
	};
}
