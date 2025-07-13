#pragma once

#include "Observer.h"

namespace Arkanoid
{
	class UBlock;
	class IGameObject;

	// Struct that contains all game objects of the game
	struct CGameState {
		CGameState() = default;

		CGameState(std::vector<std::shared_ptr<UBlock>>& Blocks,
			std::vector<std::shared_ptr<IGameObject>>& GameObjects)
		{
			this->Blocks =  Blocks;
			this->GameObjects = GameObjects;
		}

		std::vector<std::shared_ptr<UBlock>> Blocks;			// Vector of blocks
		std::vector<std::shared_ptr<IGameObject>> GameObjects;	// Vector of playable objects (ball, platform)
	};

	// State class that contains last game state blocks' positions and healt 
	class OGameState {
	public:
		OGameState();
		~OGameState() = default;

		void SaveGameState(std::shared_ptr<CGameState> GameState, int BlocksCount, int PlayerScore);
		std::shared_ptr<CGameState> GetGameState();

		int GetBlocksCount() const;
		int GetPlayerScore() const;

	private:
		int BlocksCount = 0;	// Count of breakable blocks of the field
		int PlayerScore = 0;	// How many score points the player has
		std::shared_ptr<CGameState> GameState = nullptr;	// Game state struct
	};

	class UGameProperties
	{
	public:
		UGameProperties(); 
		~UGameProperties() = default;
		
		void DeleteBlock();
		void SetBlocksCount(int Value);
		int GetBlocksCount() const;

		void DecreaseBallLife();
		void SetBallLifes(int Value);
		int GetBallLifes() const;

		void IncreasePlayerScore(int Value);
		void SetPlayerScore(int Value);
		int GetPlayerScore() const;

		void SetGameState(std::shared_ptr<CGameState> NewGameState);
		std::shared_ptr<CGameState> GetGameState();

	private:
		int BlocksCount = 0;								// Count of breakable blocks of the field
		int BallLifesCount = 3;								// Count of ball's lifes
		int PlayerScore = 0;								// How many score points the player has
		std::shared_ptr<OGameState> GameState = nullptr;	// Game state that contains last information about the game
	};

	//// Observer that subscribes on each block and ball and checks is ball out and how many blocks left
	//class OGameManager final : public IBlockObserver, public IBallObserver, public IGameManager
	//{
	//public:
	//	OGameManager() = default;
	//	~OGameManager() = default;

	//	OGameManager(int BreakableBlocks, int BallLifes);

	//	// IBlockObserver methods
	//	void BlockBroken(int Cost, const sf::Vector2f& Position) override;

	//	// IBallObserver methods
	//	void BallOut() override;

	//	// IGameManager methods
	//	void SaveGameState(std::shared_ptr<CGameState> NewGameState) override;
	//	std::shared_ptr<CGameState> GetGameState() override;

	//	void ClearGameplayType() override;
	//	bool IsGameplayTypeChanged() const override;
	//	EGameplayType GetGameplayType() const override;
	//	void DrawUI(sf::RenderWindow& Window) override;

	//private:
	//	void ChangeGameplayType(EGameplayType NewType);

	//	int BlocksCount = 0;			// Count of breakable blocks of the field
	//	int BallLifesCount = 3;			// Count of ball's lifes
	//	int PlayerScore = 0;			// How many score points the player has

	//	sf::SoundBuffer WinSound;		// Sound of a level complete
	//	sf::SoundBuffer LoseSound;		// Sound of the game over

	//	bool bIsGameplayTypeChanged = false;
	//	EGameplayType CurrentGameplayType = EGameplayType::Main;

	//	std::shared_ptr<OGameUI> UI = nullptr;				// User Interface
	//	std::shared_ptr<OGameState> GameState = nullptr;	// Game state that contains last information about the game
	//};
}