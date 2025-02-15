#include <cassert>
#include "LeaderBoardMenuState.h"
#include "../../Settings/Settings.h"
#include "../../Math/Math.h"

namespace Arkanoid
{
	SLeaderBoardMenu::SLeaderBoardMenu()
	{
		// Load textures
		bool bIsLoaded = BackgroundTexture.loadFromFile("Resources/Backgrounds/Main_menu_background.jpg");
		assert(bIsLoaded);

		// Load sounds
		bIsLoaded = MovesSound.loadFromFile("Resources/Sounds/Owlstorm__Snake_hit.wav");
		assert(bIsLoaded);

		bIsLoaded = ChoiceSound.loadFromFile("Resources/Sounds/Theevilsocks__menu-hover.wav");
		assert(bIsLoaded);

		// Set clickable buttons for menu
		std::vector<std::string> InputButtons = { "Exit" };

		// Coordinates of menu items
		float Width = static_cast<float>(SETTINGS.GetScreenWidth());
		float Height = static_cast<float>(SETTINGS.GetScreenHeight());
		float X = Width / 2.f;
		float Y = Height / 10.f;

		// Initialization of a background of the menu
		BackgroundSprite.setTexture(BackgroundTexture);
		Math::SetSize(BackgroundSprite, Width, Height);

		// Initialization of a menu title
		MenuTitle.setFont(SETTINGS.GetResources()->GetFont());
		MenuTitle.setCharacterSize(TitleTextSize);
		MenuTitle.setFillColor(Button.CommonColor);
		MenuTitle.setString("Leader board");
		MenuTitle.setOrigin(sf::Vector2f(MenuTitle.getGlobalBounds().width / 2.f, MenuTitle.getGlobalBounds().height / 2.f));
		MenuTitle.setPosition(X, Y - TitleTextSize);

		// Initialization of menu's buttons
		sf::Text MenuButton;
		float space = static_cast<float> (ButtonsTextSize);
		MenuButton.setFont(SETTINGS.GetResources()->GetFont());
		MenuButton.setCharacterSize(ButtonsTextSize);
		MenuButton.setFillColor(Button.CommonColor);

		Buttons.clear();
		Y = Height - Height / 10.f;
		for (auto& i : InputButtons) {
			MenuButton.setString(i);
			MenuButton.setOrigin(sf::Vector2f(MenuButton.getGlobalBounds().width / 2.f, MenuButton.getGlobalBounds().height / 2.f));
			MenuButton.setPosition(X, Y + space * 1.2f);
			Buttons.push_back(MenuButton);
			space += ButtonsTextSize;
		}

		// Color of the first button
		Buttons[SelectedButton].setFillColor(Button.ChosenColor);
	}

	// All menu movement and events
	void SLeaderBoardMenu::EventUpdate(const sf::Event& Event)
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
					SetNewGameState(EGameStateType::MainMenu);
				}
			}
		}
	}

	void SLeaderBoardMenu::GameplayUpdate(const float DeltaTime) {}

	void SLeaderBoardMenu::Draw(sf::RenderWindow& Window)
	{
		Window.draw(BackgroundSprite);
		Window.draw(MenuTitle);

		for (auto& i : Buttons) {
			Window.draw(i);
		}
	}

	bool SLeaderBoardMenu::IsGameStateUpdated() const
	{
		return bIsGameStateUpdated;
	}

	EGameStateType SLeaderBoardMenu::GetNewGameStateType() const
	{
		return NewGameStateType;
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	      PRIVATE WORKTOOLS         */
	/*                                  */
	/*//////////////////////////////////*/

	// Menu movement methods
	void SLeaderBoardMenu::MoveUp()
	{
		if (SelectedButton >= 0)
		{
			Buttons[SelectedButton].setFillColor(Button.CommonColor);
			--SelectedButton;

			if (SelectedButton < 0)
			{
				SelectedButton = static_cast<int> (Buttons.size()) - 1;
			}

			Buttons[SelectedButton].setFillColor(Button.ChosenColor);
		}

		SETTINGS.GetResources()->PlaySound(MovesSound);
	}

	void SLeaderBoardMenu::MoveDown()
	{
		int end = static_cast<int> (Buttons.size());

		if (SelectedButton <= end)
		{
			Buttons[SelectedButton].setFillColor(Button.CommonColor);
			++SelectedButton;

			if (SelectedButton == end)
			{
				SelectedButton = 0;
			}

			Buttons[SelectedButton].setFillColor(Button.ChosenColor);
		}

		SETTINGS.GetResources()->PlaySound(MovesSound);
	}

	// Change flag and state type 
	void SLeaderBoardMenu::SetNewGameState(EGameStateType NewState)
	{
		bIsGameStateUpdated = true;
		NewGameStateType = NewState;

		SETTINGS.GetResources()->PlaySound(ChoiceSound);
	}
}