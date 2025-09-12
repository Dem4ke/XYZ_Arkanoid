#include <cassert>
#include "MainGameplayState.h"
#include "IGameObject.h"
#include "GameObjects/Block.h"
#include "GameObjects/Bonus.h"
#include "GameObjects/Ball.h"
#include "GameObjects/Platform.h"
#include "GameObjects/DuringBonus.h"
#include "GameObjects/BonusFactory.h"
#include "LevelLoader/LevelLoader.h"
#include "Observer/GameProperties.h"
#include "PauseState/PauseState.h"
#include "UI/GameUI.h"
#include "../GameStateObserver.h"
#include "../../Settings/Settings.h"
#include "../../Math/Math.h"

namespace Arkanoid
{
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

		GameplayType = MainGameplay::EGameplayType::Main;

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
		if (GameplayType == MainGameplay::EGameplayType::Main)
		{
			if (Event.type == sf::Event::KeyReleased)
			{
				if (Event.key.code == Button.EscapeKey)
				{
					InitSubGameplayState(MainGameplay::EGameplayType::Pause);
				}
			}
		}
		else if (GameplayType != MainGameplay::EGameplayType::Main && SubGameplayState)
		{
			SubGameplayState->EventUpdate(Event);
		}
	}

	void SMainGameplay::GameplayUpdate(const float DeltaTime) 
	{
		if (GameplayType == MainGameplay::EGameplayType::Main)
		{
			// Check ball and platform collision
			if (GameObjects[1]->CheckCollision(GameObjects[0], GameObjects[0]->GetObjectType()))
			{
				SaveGameState();

				SETTINGS.GetResources()->PlaySound(HitSound);
			}

			int it = 0;
			for (auto& Block : Blocks)
			{
				if (GameObjects[1]->CheckCollision(Block, Block->GetObjectType()))
				{
					SETTINGS.GetResources()->PlaySound(HitSound);
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
					SETTINGS.GetResources()->PlaySound(HitSound);
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
			if (SubGameplayState)
			{
				SubGameplayState->GameplayUpdate(DeltaTime);
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

	void SMainGameplay::Attach(std::weak_ptr<IGameStateObserver> Observer)
	{
		Observers.push_back(Observer);
	}

	void SMainGameplay::Detach(std::weak_ptr<IGameStateObserver> Observer)
	{
		//Observers.erase(std::remove(Observers.begin(), Observers.end(), Observer.lock()), Observers.end());
	}

	void SMainGameplay::Notify(int NewGameStateType)
	{
		for (auto& i : Observers)
		{
			i.lock()->GameStateChanged(NewGameStateType);
		}
	}

	void SMainGameplay::BlockBroken(int Cost, const sf::Vector2f& Position)
	{
		GameProperties->DeleteBlock();
		GameProperties->IncreasePlayerScore(Cost);

		UI->SetScore(GameProperties->GetPlayerScore());

		if (GameProperties->GetBlocksCount() <= 0)
		{
			InitSubGameplayState(MainGameplay::EGameplayType::LevelDone);
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
			InitSubGameplayState(MainGameplay::EGameplayType::GameOver);
		}
		else
		{
			InitSubGameplayState(MainGameplay::EGameplayType::RestoreLastGameState);
		}
	}

	void SMainGameplay::BonusTaken(int Type)
	{
		// Создать текущий бонус с таймером внутри, подключить его обсервер, когда он закончится выключить бонус
		switch (Type) 
		{
		case 0:
		{
			break;
		}
		case 1:
		{
			EnableFireBallBonus();
			break;
		}
		case 2:
		{
			EnableGlassBlocksBonus();
			break;
		}
		case 3:
		{
			EnableBigPlatformBonus();
			break;
		}
		}
	}

	// Bonus time is over and we need to end bonus effect
	void SMainGameplay::BonusEnded(int ArrayNumber)
	{
		
	}

	void SMainGameplay::EnableFireBallBonus()
	{

	}

	void SMainGameplay::EnableGlassBlocksBonus()
	{

	}

	void SMainGameplay::EnableBigPlatformBonus()
	{
		Platform->
	}


	/*//////////////////////////////////*/
	/*                                  */
	/*	      PRIVATE WORKTOOLS         */
	/*                                  */
	/*//////////////////////////////////*/

	void SMainGameplay::GameStateChanged(int NewGameStateType)
	{
		switch (NewGameStateType) 
		{
		case 0:
		{
			SetNewGameState(MainGameplay::EGameStateType::MainMenu);
			break;
		}
		case 1:
		{
			InitSubGameplayState(MainGameplay::EGameplayType::Main);
			break;
		}
		}
	}

	// Create backup of game state to restore it if player lost the life
	void SMainGameplay::SaveGameState()
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
	}

	// Set the state that existed before ball went out of bounds
	void SMainGameplay::RestoreLastGameState()
	{
		Blocks.clear();
		GameObjects.clear();

		Blocks = GameProperties->GetGameState()->Blocks;
		GameObjects = GameProperties->GetGameState()->GameObjects;
		UI->SetScore(GameProperties->GetPlayerScore());

		InitSubGameplayState(MainGameplay::EGameplayType::Main);
	}

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

			// Save start information of game objects
			SaveGameState();
			InitSubGameplayState(MainGameplay::EGameplayType::Main);
		}
		else
		{
			InitSubGameplayState(MainGameplay::EGameplayType::GameOver);
		}
	}

	// Change flag and state type 
	void SMainGameplay::SetNewGameState(MainGameplay::EGameStateType NewState)
	{
		SETTINGS.GetResources()->PlaySound(ChoiceSound);
		Notify(static_cast<int>(NewState));
	}

	void SMainGameplay::InitSubGameplayState(MainGameplay::EGameplayType Type)
	{
		GameplayType = Type;

		if (SubGameplayState)
		{
			SubGameplayState = nullptr;
		}

		switch (Type)
		{
		case MainGameplay::EGameplayType::Pause:
		{
			SubGameplayState = std::make_shared<SPauseState>();
			break;
		}
		case MainGameplay::EGameplayType::GameOver:
		{
			//SubGameplayState = std::make_shared<>();
			break;
		}
		case MainGameplay::EGameplayType::LevelDone:
		{
			InitNewLevel();
			break;
		}
		case MainGameplay::EGameplayType::RestoreLastGameState:
		{
			RestoreLastGameState();
			break;
		}
		}

		if (SubGameplayState)
		{
			SubGameplayState->Init();

			// Add observer to game state
			std::shared_ptr<IGameStateSubject> GameStateSubject = std::dynamic_pointer_cast<IGameStateSubject>(SubGameplayState);
			GameStateSubject->Attach(weak_from_this());
		}
	}
}