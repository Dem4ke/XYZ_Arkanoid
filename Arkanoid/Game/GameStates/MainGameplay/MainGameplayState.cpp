#include <cassert>
#include "MainGameplayState.h"
#include "ISubGameplayState.h"
#include "LevelLoader.h"
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
		bIsLoaded = MovesSound.loadFromFile("Resources/Sounds/Owlstorm__Snake_hit.wav");
		assert(bIsLoaded);

		bIsLoaded = ChoiceSound.loadFromFile("Resources/Sounds/Theevilsocks__menu-hover.wav");
		assert(bIsLoaded);

		// Create level loader and load first level
		LevelLoader = std::make_shared<ULevelLoader>();
		LevelLoader->Load(1);
	}

	// All menu movement and events
	void SMainGameplay::EventUpdate(const sf::Event& Event)
	{
		
	}

	void SMainGameplay::GameplayUpdate(const float DeltaTime) {
		
	}

	void SMainGameplay::Draw(sf::RenderWindow& Window)
	{
		
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
		
	}
}