#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "../GameStateSubject.h"
#include "../GameStateObserver.h"
#include "../IGameState.h"
#include "../CButton.h"
#include "Observer/Observer.h"

namespace MainGameplay
{
	enum class EGameStateType : int
	{
		MainMenu = 0,
	};

	enum class EGameplayType : int
	{
		Main = 0,
		Pause,
		GameOver,
		LevelDone,
		RestoreLastGameState,
	};
}

namespace Arkanoid
{
	class IGameObject;
	class ULevelLoader;
	class UBlock;
	class UBonus;
	class UDuringBonus;
	class OGameUI;
	class UGameProperties;

	class SMainGameplay final : public IGameState, public IGameStateSubject, public IGameStateObserver,
								public IBallObserver, public IBlockObserver, public IBonusObserver, 
		public std::enable_shared_from_this<SMainGameplay>
	{
	public:
		SMainGameplay() = default;
		~SMainGameplay() = default;

		// IGameState methods
		void Init() override;
		void EventUpdate(const sf::Event& Event) override;
		void GameplayUpdate(const float DeltaTime) override;
		void Draw(sf::RenderWindow& Window) override;

		// IGameStateSubject methods
		void Attach(std::weak_ptr<IGameStateObserver> Observer) override;
		void Detach(std::weak_ptr<IGameStateObserver> Observer) override;
		void Notify(int NewGameStateType) override;

		// IBlockObserver methods
		void BlockBroken(int Cost, const sf::Vector2f& Position) override;

		// IBallObserver methods
		void BallOut() override;

		// IBonusObserver methods
		void BonusTaken(int Type) override;
		void BonusEnded(int ArrayNumber) override;

	private:
		// Bonuses
		void EnableFireBallBonus();
		void EnableGlassBlocksBonus();
		void EnableBigPlatformBonus();

		// IGameStateObserver methods
		void GameStateChanged(int NewGameStateType) override;

		// Work tools
		void SaveGameState();
		void RestoreLastGameState();

		void InitNewLevel();
		void SetNewGameState(MainGameplay::EGameStateType NewState);
		void InitSubGameplayState(MainGameplay::EGameplayType Type);

	private:
		std::shared_ptr<IGameState> SubGameplayState = nullptr;			// Sub gameplay menus (pause dialog and other)
		std::shared_ptr<ULevelLoader> LevelLoader = nullptr;			// Class to load levels from config file
		std::shared_ptr<UGameProperties> GameProperties = nullptr;		// Game properties
		std::shared_ptr<OGameUI> UI = nullptr;							// User Interface

		std::vector<std::shared_ptr<IGameObject>> GameObjects;			// Vector of playable objects (ball, platform)
		std::vector<std::shared_ptr<UBonus>> Bonuses;					// Vector of untaken bonuses
		std::vector<std::shared_ptr<UDuringBonus>> DuringBonuses;		// Vector of during bonuses
		std::vector<std::shared_ptr<UBlock>> Blocks;					// Vector of blocks
		
		MainGameplay::EGameplayType GameplayType;						// Current gameplay type which shows

		sf::Texture BackgroundTexture;									// Texture for background
		sf::Sprite BackgroundSprite;									// Sprite which shows on a background
		sf::SoundBuffer MovesSound;										// Sound of menu moves
		sf::SoundBuffer ChoiceSound;									// Sound of menu choices
		sf::SoundBuffer WinSound;										// Sound of a level complete
		sf::SoundBuffer LoseSound;										// Sound of the game over
		sf::SoundBuffer HitSound;										// Sound of ball or bonus hit
			
		CButton Button;													// Keys to work with game

		std::vector<std::weak_ptr<IGameStateObserver>> Observers;		// Observers of a state
	};
}
