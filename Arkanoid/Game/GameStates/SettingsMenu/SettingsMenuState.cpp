#include <cassert>
#include "SettingsMenuState.h"
#include "../../Settings/Settings.h"
#include "../../Math/Math.h"

namespace Arkanoid
{
	SSettingsMenu::SSettingsMenu()
	{
		// Load textures
		bool bIsLoaded = BackgroundTexture.loadFromFile("Resources/Backgrounds/Menu_background.jpg");
		assert(bIsLoaded);

		// Load sounds
		bIsLoaded = MovesSound.loadFromFile("Resources/Sounds/Owlstorm__Snake_hit.wav");
		assert(bIsLoaded);

		bIsLoaded = ChoiceSound.loadFromFile("Resources/Sounds/Theevilsocks__menu-hover.wav");
		assert(bIsLoaded);

		// Set clickable buttons for menu
		std::vector<std::string> InputButtons = { "Sounds", "Screen", "Back" };

		// Coordinates of menu items
		float Width = static_cast<float>(SETTINGS.GetScreenWidth());
		float Height = static_cast<float>(SETTINGS.GetScreenHeight());
		float X = Width / 2.f;
		float Y = Height / 3.f;

		// Initialization of a background of the menu
		BackgroundSprite.setTexture(BackgroundTexture);
		Math::SetSize(BackgroundSprite, Width, Height);

		// Initialization of a menu title
		MenuTitle.setFont(SETTINGS.GetResources()->GetFont());
		MenuTitle.setCharacterSize(TitleTextSize);
		MenuTitle.setFillColor(CommonButtonColor);
		MenuTitle.setString("Settings");
		MenuTitle.setOrigin(sf::Vector2f(MenuTitle.getGlobalBounds().width / 2.f, MenuTitle.getGlobalBounds().height / 2.f));
		MenuTitle.setPosition(X, Y - TitleTextSize);

		// Initialization of menu's buttons
		sf::Text MenuButton;
		float space = static_cast<float> (ButtonsTextSize);
		MenuButton.setFont(SETTINGS.GetResources()->GetFont());
		MenuButton.setCharacterSize(ButtonsTextSize);
		MenuButton.setFillColor(CommonButtonColor);

		Buttons.clear();
		for (auto& i : InputButtons) {
			MenuButton.setString(i);
			MenuButton.setOrigin(sf::Vector2f(MenuButton.getGlobalBounds().width / 2.f, MenuButton.getGlobalBounds().height / 2.f));
			MenuButton.setPosition(X, Y + space * 1.2f);
			Buttons.push_back(MenuButton);
			space += ButtonsTextSize;
		}

		// Color of the first button
		Buttons[SelectedButton].setFillColor(ChosenButtonColor);
	}

	// All menu movement and events
	void SSettingsMenu::EventUpdate(const sf::Event& Event)
	{
		if (Event.type == sf::Event::KeyReleased)
		{
			if (Event.key.code == Button.UpKey)
			{
				MoveUp();
			}
			else if (Event.key.code == Button.DownKey)
			{
				MoveDown();
			}
			else if (Event.key.code == Button.EscapeKey || Event.key.code == Button.EscapeKeyB)
			{
				SetNewGameState(EGameStateType::MainMenu);
			}
			else if (Event.key.code == Button.EnterKey)
			{
				if (SelectedButton == 0)
				{
					ChangeSettingsType(ESettingsType::Sounds);
				}
				else if (SelectedButton == 1)
				{
					ChangeSettingsType(ESettingsType::Video);
				}
				else if (SelectedButton == 2)
				{
					SetNewGameState(EGameStateType::MainMenu);
				}
			}
		}
	}

	void SSettingsMenu::GameplayUpdate(const float DeltaTime) {}

	void SSettingsMenu::Draw(sf::RenderWindow& Window)
	{
		Window.draw(BackgroundSprite);

		switch (SettingsType)
		{
		case ESettingsType::Main:
		{
			Window.draw(MenuTitle);

			for (auto& i : Buttons) {
				Window.draw(i);
			}

			break;
		}
		case ESettingsType::Sounds:
		{
			//SoundMenu->Draw(Window);
			break;
		}
		case ESettingsType::Video:
		{
			//VideoMenu->Draw(Window);
			break;
		}
		}
	}

	bool SSettingsMenu::IsGameStateUpdated() const
	{
		return bIsGameStateUpdated;
	}

	EGameStateType SSettingsMenu::GetNewGameStateType() const
	{
		return NewGameStateType;
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	      PRIVATE WORKTOOLS         */
	/*                                  */
	/*//////////////////////////////////*/

	// Menu movement methods
	void SSettingsMenu::MoveUp()
	{
		if (SelectedButton >= 0)
		{
			Buttons[SelectedButton].setFillColor(CommonButtonColor);
			--SelectedButton;

			if (SelectedButton < 0)
			{
				SelectedButton = Buttons.size() - 1;
			}

			Buttons[SelectedButton].setFillColor(ChosenButtonColor);
		}

		SETTINGS.GetResources()->PlaySound(MovesSound);
	}

	void SSettingsMenu::MoveDown()
	{
		size_t end = Buttons.size();

		if (SelectedButton <= end)
		{
			Buttons[SelectedButton].setFillColor(CommonButtonColor);
			++SelectedButton;

			if (SelectedButton == end)
			{
				SelectedButton = 0;
			}

			Buttons[SelectedButton].setFillColor(ChosenButtonColor);
		}

		SETTINGS.GetResources()->PlaySound(MovesSound);
	}

	// Change flag and state type 
	void SSettingsMenu::SetNewGameState(EGameStateType NewState)
	{
		bIsGameStateUpdated = true;
		NewGameStateType = NewState;

		SETTINGS.GetResources()->PlaySound(ChoiceSound);
	}

	// Create new sub settings menu
	void SSettingsMenu::ChangeSettingsType(ESettingsType NewType)
	{
		SettingsType = NewType;

		switch (SettingsType)
		{
		case ESettingsType::Sounds: 
		{
			break;
		}
		case ESettingsType::Video:
		{
			break;
		}
		}
	}
}