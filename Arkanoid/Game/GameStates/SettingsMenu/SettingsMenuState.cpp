#include <cassert>
#include "SettingsMenuState.h"
#include "SoundSettingsMenuState.h"
#include "VideoSettingsMenuState.h"
#include "../../Settings/Settings.h"
#include "../../Math/Math.h"

namespace Arkanoid
{
	void SSettingsMenu::Init()
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
		MenuTitle.setFillColor(Button.CommonColor);
		MenuTitle.setString("Settings");
		MenuTitle.setOrigin(sf::Vector2f(MenuTitle.getGlobalBounds().width / 2.f, MenuTitle.getGlobalBounds().height / 2.f));
		MenuTitle.setPosition(X, Y - TitleTextSize);

		// Initialization of menu's buttons
		sf::Text MenuButton;
		float space = static_cast<float> (ButtonsTextSize);
		MenuButton.setFont(SETTINGS.GetResources()->GetFont());
		MenuButton.setCharacterSize(ButtonsTextSize);
		MenuButton.setFillColor(Button.CommonColor);

		Buttons.clear();
		for (auto& i : InputButtons) {
			MenuButton.setString(i);
			MenuButton.setOrigin(sf::Vector2f(MenuButton.getGlobalBounds().width / 2.f, MenuButton.getGlobalBounds().height / 2.f));
			MenuButton.setPosition(X, Y + space * 1.2f);
			Buttons.push_back(MenuButton);
			space += ButtonsTextSize;
		}

		// Color of the first button
		Buttons[SelectedButton].setFillColor(Button.ChosenColor);

		SettingsType = SettingsMenu::ESettingsType::Main;
	}

	// All menu movement and events
	void SSettingsMenu::EventUpdate(const sf::Event& Event)
	{
		if (SettingsType == SettingsMenu::ESettingsType::Main) {
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
					SetNewGameState(SettingsMenu::EGameStateType::MainMenu);
				}
				else if (Event.key.code == Button.EnterKey)
				{
					if (SelectedButton == 0)
					{
						SettingsType = SettingsMenu::ESettingsType::Sounds;
						InitSubSettingsMenu(SettingsType);
					}
					else if (SelectedButton == 1)
					{
						SettingsType = SettingsMenu::ESettingsType::Video;
						InitSubSettingsMenu(SettingsType);
					}
					else if (SelectedButton == 2)
					{
						SetNewGameState(SettingsMenu::EGameStateType::MainMenu);
					}
				}
			}
		}
		else 
		{
			if (SubMenu)
			{
				SubMenu->EventUpdate(Event);
			}
		}
	}

	void SSettingsMenu::GameplayUpdate(const float DeltaTime) {}

	void SSettingsMenu::Draw(sf::RenderWindow& Window)
	{
		Window.draw(BackgroundSprite);

		if (SettingsType == SettingsMenu::ESettingsType::Main)
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

	void SSettingsMenu::Attach(std::weak_ptr<IGameStateObserver> Observer)
	{
		Observers.push_back(Observer);
	}

	void SSettingsMenu::Detach(std::weak_ptr<IGameStateObserver> Observer)
	{
		//Observers.erase(std::remove(Observers.begin(), Observers.end(), Observer.lock()), Observers.end());
	}

	void SSettingsMenu::Notify(int NewGameStateType)
	{
		for (auto& i : Observers)
		{
			i.lock()->GameStateChanged(NewGameStateType);
		}
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	      PRIVATE WORKTOOLS         */
	/*                                  */
	/*//////////////////////////////////*/

	void SSettingsMenu::GameStateChanged(int NewGameStateType)
	{
		SettingsType = SettingsMenu::ESettingsType::Main;

		Init();
	}

	// Menu movement methods
	void SSettingsMenu::MoveUp()
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

	void SSettingsMenu::MoveDown()
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
	void SSettingsMenu::SetNewGameState(SettingsMenu::EGameStateType NewState)
	{
		SETTINGS.GetResources()->PlaySound(ChoiceSound);
		Notify(static_cast<int>(NewState));
	}

	void SSettingsMenu::InitSubSettingsMenu(SettingsMenu::ESettingsType Type)
	{
		if (SubMenu)
		{
			SubMenu = nullptr;
		}

		switch (Type)
		{
		case SettingsMenu::ESettingsType::Sounds:
		{
			SubMenu = std::make_shared<SSoundSettingsMenu>();
			break;
		}
		case SettingsMenu::ESettingsType::Video:
		{
			SubMenu = std::make_shared<SVideoSettingMenu>();
			break;
		}
		}

		SubMenu->Init();

		// Add observer to game state
		std::shared_ptr<IGameStateSubject> GameStateSubject = std::dynamic_pointer_cast<IGameStateSubject>(SubMenu);
		GameStateSubject->Attach(weak_from_this());
	}
}