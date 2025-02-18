#include <cassert>
#include "MainGameplayState.h"
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

		// Create level
		// Create blocks from level config that loaded above
	}

	// All menu movement and events
	void SMainGameplay::EventUpdate(const sf::Event& Event)
	{
		if (SettingsType == ESettingsType::Main) {
			if (Event.type == sf::Event::KeyReleased)
			{
				if (Event.key.code == Button.EscapeKey || Event.key.code == Button.EscapeKeyB)
				{
					//SetNewGameState(EGameStateType::MainMenu);
				}
			}
		}
		else
		{
			if (SubMenu->IsSettingsTypeChanged())
			{
				Init();
				SettingsType = SubMenu->GetNewSettingsType();
				InitSubSettingsMenu(SettingsType);
			}

			if (SubMenu)
			{
				SubMenu->EventUpdate(Event);
			}
		}
	}

	void SMainGameplay::GameplayUpdate(const float DeltaTime) {
		if (SettingsType != ESettingsType::Main) {
			if (SubMenu->IsSettingsTypeChanged())
			{
				Init();
				SettingsType = SubMenu->GetNewSettingsType();
				InitSubSettingsMenu(SettingsType);
			}
		}
	}

	void SMainGameplay::Draw(sf::RenderWindow& Window)
	{
		Window.draw(BackgroundSprite);

		if (SettingsType == ESettingsType::Main)
		{
			Window.draw(MenuTitle);

			for (auto& i : Buttons)
			{
				Window.draw(i);
			}
		}
		else
		{
			SubMenu->Draw(Window);
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
		if (SubGameplayState)
		{
			SubGameplayState = nullptr;
		}

		switch (Type)
		{
		case EGameplayType::Pause:
		{
			SubGameplayState = std::make_shared<STSoundSettingsMenu>();
			break;
		}
		}
	}
}