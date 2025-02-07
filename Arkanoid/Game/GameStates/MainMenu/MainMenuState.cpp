#include <cassert>
#include "MainMenuState.h"
#include "../../Settings/Settings.h"
#include "../../Math/Math.h"

namespace Arkanoid
{
	SMainMenu::SMainMenu() 
	{
		// Get game settings
		UGameSettings* GameSettings = UGameSettings::GetGameSettings();

		// Load textures
		bool bIsLoaded = BackgroundTexture.loadFromFile("../../../Game/Resources/Backgrounds/Main_background.jpg");
		assert(bIsLoaded);

		// Load sounds
		bIsLoaded = MovesSound.loadFromFile("../../../Game/Resources / Sounds / Owlstorm__Snake_hit.wav");
		assert(bIsLoaded);

		bIsLoaded = ChoiceSound.loadFromFile("../../../Game/Resources/Sounds/Theevilsocks__menu-hover.wav");
		assert(bIsLoaded);

		// Set clickable buttons for menu
		std::vector<std::string> InputButtons = { "Play game", "Leader board", "Settings", "Exit" };

		// Coordinates of menu items
		float Width = static_cast<float>(GameSettings->GetScreenWidth());
		float Height = static_cast<float>(GameSettings->GetScreenHeight());
		float X = Width / 2.f;
		float Y = Height / 3.f;

		// Initialization of a background of the menu
		BackgroundSprite.setTexture(BackgroundTexture);
		Math::SetSize(BackgroundSprite, Width, Height);

		// Initialization of a menu title
		MenuTitle.setFont(GameSettings->GetResources()->GetFont());
		MenuTitle.setCharacterSize(TitleTextSize);
		MenuTitle.setFillColor(CommonButtonColor);
		MenuTitle.setString("Arkanoid");
		MenuTitle.setOrigin(sf::Vector2f(MenuTitle.getGlobalBounds().width / 2.f, MenuTitle.getGlobalBounds().height / 2.f));
		MenuTitle.setPosition(X, Y - TitleTextSize);

		// Initialization of menu's buttons
		sf::Text MenuButton;
		float space = static_cast<float> (ButtonsTextSize);
		MenuButton.setFont(GameSettings->GetResources()->GetFont());
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

	SMainMenu::~SMainMenu() {}

	// All menu movement and events
	void SMainMenu::EventUpdate(const sf::Event& Event) 
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
				SetNewGameState(EGameStateType::ExitMenu);
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
					SetNewGameState(EGameStateType::ExitMenu);
				}
			}
		}
	}

	void SMainMenu::GameplayUpdate(const float DeltaTime) {}

	void SMainMenu::Draw(sf::RenderWindow& Window) 
	{
		Window.draw(BackgroundSprite);
		Window.draw(MenuTitle);

		for (auto& i : Buttons) {
			Window.draw(i);
		}
	}

	bool SMainMenu::IsGameStateUpdated() const
	{
		return bIsGameStateUpdated;
	}

	EGameStateType SMainMenu::GetNewGameStateType() const
	{
		return NewGameStateType;
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	      PRIVATE WORKTOOLS         */
	/*                                  */
	/*//////////////////////////////////*/

	// Menu movement methods
	void SMainMenu::MoveUp()
	{
		// Get game settings
		UGameSettings* GameSettings = UGameSettings::GetGameSettings();

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

		GameSettings->GetResources()->PlaySound(MovesSound);
	}

	void SMainMenu::MoveDown()
	{
		// Get game settings
		UGameSettings* GameSettings = UGameSettings::GetGameSettings();

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

		GameSettings->GetResources()->PlaySound(ChoiceSound);
	}

	// Change flag and state type 
	void SMainMenu::SetNewGameState(EGameStateType NewState)
	{
		// Get game settings
		UGameSettings* GameSettings = UGameSettings::GetGameSettings();

		bIsGameStateUpdated = true;
		NewGameStateType = NewState;

		GameSettings->GetResources()->PlaySound(MovesSound);
	}
}