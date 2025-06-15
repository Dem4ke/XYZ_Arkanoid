#include <cassert>
#include "MainGameplayState.h"
#include "ISubGameplayState.h"
#include "IGameObject.h"
#include "GameObjects/Block.h"
#include "GameObjects/Ball.h"
#include "GameObjects/Platform.h"
#include "LevelLoader/LevelLoader.h"
#include "Observer/GameManager.h"
#include "PauseState/PauseState.h"
#include "../../Settings/Settings.h"
#include "../../Math/Math.h"

namespace Arkanoid
{
	SMainGameplay::SMainGameplay()
	{
		// Load textures
		bool bIsLoaded = BackgroundTexture.loadFromFile("Resources/Backgrounds/Main_background.jpg");
		assert(bIsLoaded);

		// Load sounds
		bIsLoaded = ChoiceSound.loadFromFile("Resources/Sounds/Theevilsocks__menu-hover.wav");
		assert(bIsLoaded);

		// Initialization of a background of the game
		float Width = static_cast<float>(SETTINGS.GetScreenWidth());
		float Height = static_cast<float>(SETTINGS.GetScreenHeight());
		BackgroundSprite.setTexture(BackgroundTexture);
		Math::SetSize(BackgroundSprite, Width, Height);

		// Create level loader and load first level
		LevelLoader = std::make_shared<ULevelLoader>();
		InitNewLevel();
	}

	// All menu movement and events
	void SMainGameplay::EventUpdate(const sf::Event& Event) 
	{
		if (GameplayType == EGameplayType::Main)
		{
			if (Event.type == sf::Event::KeyReleased)
			{
				if (Event.key.code == Button.EscapeKey)
				{
					InitSubGameplayState(EGameplayType::Pause);
				}
			}
		}
		else if (GameplayType != EGameplayType::Main && SubGameplayState)
		{
			SubGameplayState->EventUpdate(Event);
		}
	}

	void SMainGameplay::GameplayUpdate(const float DeltaTime) 
	{
		if (GameplayType == EGameplayType::Main)
		{
			// Check ball and platform collision
			// ѕри вылете м€ча отсюда пропадают м€ч и платформа
			if (GameObjects[1]->CheckCollision(GameObjects[0], GameObjects[0]->GetObjectType()))
			{
				// Save state of the game
				std::shared_ptr<CGameState> GameState = std::make_shared<CGameState>(Blocks, GameObjects);
				Observer->SaveGameState(GameState);
			}

			int it = 0;
			for (auto& Block : Blocks)
			{
				if (GameObjects[1]->CheckCollision(Block, Block->GetObjectType()))
				{
					break;
				}

				if (Block->IsDestroyed()) 
				{
					Blocks.erase(Blocks.cbegin() + it);
					break;
				}

				++it;

				Block->Update(DeltaTime);
			}

			for (auto& Object : GameObjects)
			{
				Object->Update(DeltaTime);
			}

			if (Observer->IsGameplayTypeChanged())
			{
				GameplayType = Observer->GetGameplayType();
				InitSubGameplayState(GameplayType);
			}
		}
		else 
		{
			if (SubGameplayState && SubGameplayState->IsGameplayTypeChanged())
			{
				GameplayType = SubGameplayState->GetNewGameplayType();
				InitSubGameplayState(GameplayType);
			}
		}
	}

	void SMainGameplay::Draw(sf::RenderWindow& Window)
	{
		Window.draw(BackgroundSprite);

		for (auto& Block : Blocks)
		{
			Block->Draw(Window);
		}

		for (auto& Object : GameObjects)
		{
			Object->Draw(Window);
		}

		if (SubGameplayState)
		{
			SubGameplayState->Draw(Window);
		}
	}

	bool SMainGameplay::IsGameStateUpdated() const
	{
		return bIsGameStateUpdated;
	}

	EGameStateType SMainGameplay::GetNewGameStateType() const
	{
		return NewGameStateType;
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	      PRIVATE WORKTOOLS         */
	/*                                  */
	/*//////////////////////////////////*/

	void SMainGameplay::InitNewLevel()
	{
		Blocks.clear();
		GameObjects.clear();
		GameplayType = EGameplayType::Main;

		if (LevelLoader->GetCurrentLevel() <= 3)
		{
			LevelLoader->Load(LevelLoader->GetCurrentLevel());

			Blocks = LevelLoader->GetBlocks();
			GameObjects = LevelLoader->GetGameObjects();
			Observer = std::make_shared<OGameManager>(LevelLoader->GetBreackableBlocksCount(), 3);

			// Add observers
			std::shared_ptr<IBlockObserver>BlockObserver = std::dynamic_pointer_cast<IBlockObserver>(Observer);
			
			for (auto& i : Blocks)
			{
				i->Attach(BlockObserver);
			}
			
			std::shared_ptr<UBall> Ball = std::dynamic_pointer_cast<UBall>(GameObjects[1]);
			std::shared_ptr<IBallObserver> BallObserver = std::dynamic_pointer_cast<IBallObserver>(Observer);
			Ball->Attach(BallObserver);
		}
	}

	// Set the state that existed before ball went out of bounds
	void SMainGameplay::RecreateBall()
	{
		Blocks = Observer->GetGameState()->Blocks;
		GameObjects = Observer->GetGameState()->GameObjects;

		InitSubGameplayState(EGameplayType::Main);
		Observer->ClearGameplayType();
	}

	// Change flag and state type 
	void SMainGameplay::SetNewGameState(EGameStateType NewState)
	{
		bIsGameStateUpdated = true;
		NewGameStateType = NewState;

		SETTINGS.GetResources()->PlaySound(ChoiceSound);
	}

	void SMainGameplay::InitSubGameplayState(EGameplayType Type)
	{
		GameplayType = Type;

		if (SubGameplayState)
		{
			SubGameplayState = nullptr;
		}

		switch (Type)
		{
		case EGameplayType::Pause:
		{
			SubGameplayState = std::make_shared<SGPauseState>();
			break;
		}
		case EGameplayType::GameOver:
		{
			//SubGameplayState = std::make_shared<>();
			break;
		}
		case EGameplayType::LevelDone:
		{
			InitNewLevel();
			break;
		}
		case EGameplayType::RecreateBall:
		{
			RecreateBall();
			break;
		}
		}
	}
}