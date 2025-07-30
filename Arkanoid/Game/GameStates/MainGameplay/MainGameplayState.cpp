#include <cassert>
#include "MainGameplayState.h"
#include "ISubGameplayState.h"
#include "IGameObject.h"
#include "GameObjects/Block.h"
#include "GameObjects/Bonus.h"
#include "GameObjects/Ball.h"
#include "GameObjects/Platform.h"
#include "GameObjects/BonusFactory.h"
#include "LevelLoader/LevelLoader.h"
#include "Observer/GameProperties.h"
#include "PauseState/PauseState.h"
#include "UI/GameUI.h"
#include "../../Settings/Settings.h"
#include "../../Math/Math.h"

namespace Arkanoid
{
	SMainGameplay::SMainGameplay()
	{
	}

	void SMainGameplay::Init()
	{
		// Load textures
		bool bIsLoaded = BackgroundTexture.loadFromFile("Resources/Backgrounds/Main_background.jpg");
		assert(bIsLoaded);

		// Load sounds
		bIsLoaded = ChoiceSound.loadFromFile("Resources/Sounds/Theevilsocks__menu-hover.wav");
		assert(bIsLoaded);

		bIsLoaded = WinSound.loadFromFile("Resources/Sounds/AppleEat.wav");
		assert(bIsLoaded);

		bIsLoaded = LoseSound.loadFromFile("Resources/Sounds/Maodin204__Lose.wav");
		assert(bIsLoaded);

		bIsLoaded = HitSound.loadFromFile("Resources/Sounds/Owlstorm__Snake_hit.wav");
		assert(bIsLoaded);

		GameProperties = std::make_shared<UGameProperties>();

		UI = std::make_shared<OGameUI>();
		UI->SetScore(GameProperties->GetPlayerScore());
		UI->SetBallLifes(GameProperties->GetBallLifes());

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
			if (GameObjects[1]->CheckCollision(GameObjects[0], GameObjects[0]->GetObjectType()))
			{
				// Create copy of game objects and save them
				std::vector<std::shared_ptr<UBlock>> CopiedBlocks;
				std::vector<std::shared_ptr<IGameObject>> CopiedGameOjects;

				for (auto& i : Blocks) 
				{
					std::shared_ptr<UBlock> CopiedBlock = std::dynamic_pointer_cast<UBlock>(i->clone());
					CopiedBlocks.push_back(CopiedBlock);
				}

				for (auto& i : GameObjects)
				{
					CopiedGameOjects.push_back(i->clone());
				}

				std::shared_ptr<CGameState> GameState = std::make_shared<CGameState>(CopiedBlocks, CopiedGameOjects);
				GameProperties->SetGameState(GameState);

				SETTINGS.GetResources()->PlaySound(HitSound);
			}

			int it = 0;
			for (auto& Block : Blocks)
			{
				if (GameObjects[1]->CheckCollision(Block, Block->GetObjectType()))
				{
					SETTINGS.GetResources()->PlaySound(HitSound);
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

			it = 0;
			for (auto& Bonus : Bonuses)
			{
				if (Bonus->CheckCollision(GameObjects[0], GameObjects[0]->GetObjectType()))
				{
					break;
				}

				if (Bonus->IsDestroyed())
				{
					Bonuses.erase(Bonuses.begin() + it);
					break;
				}

				++it;

				Bonus->Update(DeltaTime);
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
		UI->Draw(Window);

		for (auto& Block : Blocks)
		{
			Block->Draw(Window);
		}

		for (auto& Object : GameObjects)
		{
			Object->Draw(Window);
		}

		for (auto& Bonus : Bonuses)
		{
			Bonus->Draw(Window);
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

	void SMainGameplay::BlockBroken(int Cost, const sf::Vector2f& Position)
	{
		GameProperties->DeleteBlock();
		GameProperties->IncreasePlayerScore(Cost);

		UI->SetScore(GameProperties->GetPlayerScore());

		if (GameProperties->GetBlocksCount() <= 0)
		{
			InitSubGameplayState(EGameplayType::LevelDone);
			return;
		}

		if (static_cast<int> (rand() / (float)RAND_MAX * 100) < 100)
		{
			std::unique_ptr<IBonusFactory> BonusFactory;

			int Index = static_cast<int> (rand() / (float)RAND_MAX * 2);

			switch (Index)
			{
			case 0:
			{
				BonusFactory = std::make_unique<UFireBallBonusFactory>();
				break;
			}
			case 1:
			{
				BonusFactory = std::make_unique<UGlassBlocksBonusFactory>();
				break;
			}
			case 2:
			{
				BonusFactory = std::make_unique<UBigPlatformBonusFactory>();
				break;
			}
			}

			std::shared_ptr<UBonus> NewBonus = BonusFactory->CreateBonus(Position);

			Bonuses.push_back(NewBonus);
			Bonuses[Bonuses.size() - 1]->Attach(weak_from_this());
		}
	}

	void SMainGameplay::BallOut()
	{
		GameProperties->DecreaseBallLife();
		UI->SetBallLifes(GameProperties->GetBallLifes());

		if (GameProperties->GetBallLifes() <= 0)
		{
			InitSubGameplayState(EGameplayType::GameOver);
		}
		else
		{
			InitSubGameplayState(EGameplayType::RecreateBall);
		}
	}

	void SMainGameplay::BonusTaken(int Type)
	{
		switch (Type) 
		{
		case 0:
		{
			break;
		}
		case 1:
		{

			break;
		}
		case 2:
		{

			break;
		}
		case 3:
		{

			break;
		}
		}
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	      PRIVATE WORKTOOLS         */
	/*                                  */
	/*//////////////////////////////////*/

	void SMainGameplay::InitNewLevel()
	{
		if (LevelLoader->GetCurrentLevel() <= 3)
		{
			LevelLoader->Load(LevelLoader->GetCurrentLevel());

			Blocks = LevelLoader->GetBlocks();
			GameObjects = LevelLoader->GetGameObjects();
			GameProperties->SetBlocksCount(LevelLoader->GetBreackableBlocksCount());

			LevelLoader->Clear();

			// Add observers
			for (auto& i : Blocks)
			{
				i->Attach(weak_from_this());
			}
			
			std::shared_ptr<UBall> Ball = std::dynamic_pointer_cast<UBall>(GameObjects[1]);
			Ball->Attach(weak_from_this());

			InitSubGameplayState(EGameplayType::Main);
		}
		else
		{
			InitSubGameplayState(EGameplayType::GameOver);
		}
	}

	// Set the state that existed before ball went out of bounds
	void SMainGameplay::RecreateBall()
	{
		Blocks.clear();
		GameObjects.clear();

		Blocks = GameProperties->GetGameState()->Blocks;
		GameObjects = GameProperties->GetGameState()->GameObjects;
		UI->SetScore(GameProperties->GetPlayerScore());

		InitSubGameplayState(EGameplayType::Main);
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