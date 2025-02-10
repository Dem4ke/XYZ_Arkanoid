#include <cassert>
#include "SoundSettingsMenuState.h"
#include "../../Settings/Settings.h"
#include "../../Math/Math.h"

namespace Arkanoid
{
	STSoundSettingsMenu::STSoundSettingsMenu()
	{
		// Load sounds
		bool bIsLoaded = MovesSound.loadFromFile("Resources/Sounds/Owlstorm__Snake_hit.wav");
		assert(bIsLoaded);

		bIsLoaded = ChoiceSound.loadFromFile("Resources/Sounds/Theevilsocks__menu-hover.wav");
		assert(bIsLoaded);

		// Set clickable buttons for menu
		std::vector<std::string> InputButtons = { "Sounds : on", "Music : on", "Apply", "Back"};

		// Coordinates of menu items
		float Width = static_cast<float>(SETTINGS.GetScreenWidth());
		float Height = static_cast<float>(SETTINGS.GetScreenHeight());
		float X = Width / 2.f;
		float Y = Height / 3.f;


		// Initialization of a menu title
		MenuTitle.setFont(SETTINGS.GetResources()->GetFont());
		MenuTitle.setCharacterSize(TitleTextSize);
		MenuTitle.setFillColor(CommonButtonColor);
		MenuTitle.setString("Sound settings");
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
	void STSoundSettingsMenu::EventUpdate(const sf::Event& Event)
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
					if (Buttons[0].getString() == "Sounds: On") 
					{
						Buttons[0].setString("Sounds: Off");
						SETTINGS.GetResources()->PlaySound(ChoiceSound);
						SETTINGS.GetResources()->SetSoundsVolume(0.f);
					}
					else if (Buttons[0].getString() == "Sounds: Off")
					{
						Buttons[0].setString("Sounds: On");
						SETTINGS.GetResources()->PlaySound(ChoiceSound);
						SETTINGS.GetResources()->SetSoundsVolume(5.f);
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

	void STSoundSettingsMenu::Draw(sf::RenderWindow& Window)
	{
		Window.draw(MenuTitle);

		for (auto& i : Buttons) {
			Window.draw(i);
		}
	}

	bool STSoundSettingsMenu::IsSettingsTypeChanged() const
	{
		return bIsSettingsTypeUpdated;
	}

	ESettingsType STSoundSettingsMenu::GetNewSettingsType() const
	{
		return SettingsType;
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	      PRIVATE WORKTOOLS         */
	/*                                  */
	/*//////////////////////////////////*/

	// Menu movement methods
	void STSoundSettingsMenu::MoveUp()
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

	void STSoundSettingsMenu::MoveDown()
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
	void STSoundSettingsMenu::ChangeSettingsType(ESettingsType NewType)
	{
		bIsSettingsTypeUpdated = true;
		SettingsType = NewType;
		
		SETTINGS.GetResources()->PlaySound(ChoiceSound);
	}
}