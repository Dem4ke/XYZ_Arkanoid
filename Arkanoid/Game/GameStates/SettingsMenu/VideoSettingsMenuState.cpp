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
		std::vector<std::string> InputButtons = { "Sound", "Video", "Back" };

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
		int selectedButton_ = 0;
		Buttons[selectedButton_].setFillColor(ChosenButtonColor);
	}

	// All menu movement and events
	void SSettingsMenu::EventUpdate(const sf::Event& Event)
	{
		if (Event.type == sf::Event::KeyReleased)
		{
			if (Event.key.code == UpKey)
			{
				MoveUp();
			}
			else if (Event.key.code == DownKey)
			{
				MoveDown();
			}
			else if (Event.key.code == EscapeKey || Event.key.code == EscapeKeyB)
			{
				SetNewGameState(EGameStateType::MainMenu);
			}
			else if (Event.key.code == EnterKey)
			{
				if (SelectedButton == 0)
				{
					SetNewGameState(EGameStateType::MainGameplay);
				}
				else if (SelectedButton == 1)
				{
					SetNewGameState(EGameStateType::LeaderBoardMenu);
				}
				else if (SelectedButton == 2)
				{
					SetNewGameState(EGameStateType::SettingsMenu);
				}
				else if (SelectedButton == 3)
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
		Window.draw(MenuTitle);

		for (auto& i : Buttons) {
			Window.draw(i);
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
}