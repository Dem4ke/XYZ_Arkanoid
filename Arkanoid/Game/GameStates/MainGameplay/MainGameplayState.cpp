#include <cassert>
#include "MainGameplayState.h"
#include "ISubGameplayState.h"
#include "IGameObject.h"
#include "GameObjects/Block.h"
#include "GameObjects/Ball.h"
#include "GameObjects/Platform.h"
#include "LevelLoader/LevelLoader.h"
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
		LevelLoader->Load(1);

		Blocks = LevelLoader->GetBlocks();
		GameObjects = LevelLoader->GetGameObjects();
	}

	// All menu movement and events
	void SMainGameplay::EventUpdate(const sf::Event& Event) 
	{
		if (GameplayType != EGameplayType::Main && SubGameplayState)
		{
			SubGameplayState->EventUpdate(Event);
		}
	}

	void SMainGameplay::GameplayUpdate(const float DeltaTime) 
	{
		if (GameplayType == EGameplayType::Main)
		{
			GameObjects[1]->CheckCollision(GameObjects[0], GameObjects[0]->GetObjectType());

			for (auto& Block : Blocks)
			{
				GameObjects[1]->CheckCollision(Block, Block->GetObjectType());
			}

			for (auto& Object : GameObjects)
			{
				Object->Update(DeltaTime);
			}

			/*if (GameObjects[1]->IsObjectCrashed())
			{
				InitSubGameplayState(EGameplayType::GameOver);
			}*/
		}
		else {
			if (SubGameplayState->IsGameplayTypeChanged())
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

	// Change flag and state type 
	void SMainGameplay::SetNewGameState(EGameStateType NewState)
	{
		bIsGameStateUpdated = true;
		NewGameStateType = NewState;

		SETTINGS.GetResources()->PlaySound(ChoiceSound);
	}

	void SMainGameplay::InitSubGameplayState(EGameplayType Type)
	{
		/*if (SubGameplayState)
		{
			SubGameplayState = nullptr;
		}

		switch (Type)
		{
		case EGameplayType::Pause:
		{
			SubGameplayState = std::make_shared<>();
			break;
		}
		case EGameplayType::GameOver:
		{
			SubGameplayState = std::make_shared<>();
			break;
		}
		}*/
	}
}