#include <cassert>
#include "VideoSettingsMenuState.h"
#include "../../Settings/Settings.h"
#include "../../Math/Math.h"

namespace Arkanoid
{
	STVideoSettingMenu::STVideoSettingMenu()
	{
		// Load sounds
		bool bIsLoaded = MovesSound.loadFromFile("Resources/Sounds/Owlstorm__Snake_hit.wav");
		assert(bIsLoaded);

		bIsLoaded = ChoiceSound.loadFromFile("Resources/Sounds/Theevilsocks__menu-hover.wav");
		assert(bIsLoaded);

		// Set clickable buttons for menu
		std::string Fullscreen = SETTINGS.GetFullscreenInfo() == 1 ? "Fullscreen: Yes" : "Fullscreen: No";
		std::string Resolution = "Resolution" + std::to_string(SETTINGS.GetScreenWidth()) + " x " + std::to_string(SETTINGS.GetScreenHeight());
		std::vector<std::string> InputButtons = { Fullscreen, Resolution, "Apply", "Back"};

		// Coordinates of menu items
		float Width = static_cast<float>(SETTINGS.GetScreenWidth());
		float Height = static_cast<float>(SETTINGS.GetScreenHeight());
		float X = Width / 2.f;
		float Y = Height / 3.f;


		// Initialization of a menu title
		MenuTitle.setFont(SETTINGS.GetResources()->GetFont());
		MenuTitle.setCharacterSize(TitleTextSize);
		MenuTitle.setFillColor(CommonButtonColor);
		MenuTitle.setString("Video settings");
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
	void STVideoSettingMenu::EventUpdate(const sf::Event& Event)
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
				ChangeSettingsType(ESettingsType::Main);
			}
			else if (Event.key.code == Button.EnterKey)
			{
				if (SelectedButton == 0)
				{
					if (Buttons[0].getString() == "Fullscreen: Yes")
					{
						Buttons[0].setString("Fullscreen: No");
						SETTINGS.GetResources()->PlaySound(ChoiceSound);
						SETTINGS.SetFullscreenInfo(0);
					}
					else if (Buttons[0].getString() == "Fullscreen: No")
					{
						Buttons[0].setString("Fullscreen: Yes");
						SETTINGS.GetResources()->PlaySound(ChoiceSound);
						SETTINGS.SetFullscreenInfo(1);
					}
				}
				else if (SelectedButton == 1)
				{
					if (Buttons[1].getString() == "Music: On")
					{
						Buttons[1].setString("Music: Off");
						SETTINGS.GetResources()->PlaySound(ChoiceSound);
						SETTINGS.GetResources()->StopBackgroundMusic();
					}
					else if (Buttons[1].getString() == "Music: Off")
					{
						Buttons[1].setString("Music: On");
						SETTINGS.GetResources()->PlaySound(ChoiceSound);
						SETTINGS.GetResources()->PlayBackgroundMusic();
					}
				}
				else if (SelectedButton == 2)
				{
					ChangeSettingsType(ESettingsType::Main);
				}
			}
		}
	}

	void STVideoSettingMenu::Draw(sf::RenderWindow& Window)
	{
		Window.draw(MenuTitle);

		for (auto& i : Buttons) {
			Window.draw(i);
		}
	}

	bool STVideoSettingMenu::IsSettingsTypeChanged() const
	{
		return bIsSettingsTypeUpdated;
	}

	ESettingsType STVideoSettingMenu::GetNewSettingsType() const
	{
		return SettingsType;
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	      PRIVATE WORKTOOLS         */
	/*                                  */
	/*//////////////////////////////////*/

	// Menu movement methods
	void STVideoSettingMenu::MoveUp()
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

	void STVideoSettingMenu::MoveDown()
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

	// Method to change type of settings menu
	void STVideoSettingMenu::ChangeSettingsType(ESettingsType NewType)
	{
		bIsSettingsTypeUpdated = true;
		SettingsType = NewType;

		SETTINGS.GetResources()->PlaySound(ChoiceSound);
	}
}