#include <cassert>
#include "ResolutionSettingsMenu.h"
#include "../../Settings/Settings.h"
#include "../../Math/Math.h"

namespace Arkanoid
{
	STResolutionSettingsMenu::STResolutionSettingsMenu()
	{
		// Load sounds
		bool bIsLoaded = MovesSound.loadFromFile("Resources/Sounds/Owlstorm__Snake_hit.wav");
		assert(bIsLoaded);

		bIsLoaded = ChoiceSound.loadFromFile("Resources/Sounds/Theevilsocks__menu-hover.wav");
		assert(bIsLoaded);

		std::vector<std::string> InputButtons = { "1280 x 720", "1920 x 1080", "2560 x 1440" };

		// Coordinates of menu items
		float Width = static_cast<float>(SETTINGS.GetScreenWidth());
		float Height = static_cast<float>(SETTINGS.GetScreenHeight());
		float X = Width / 2.f + ButtonsTextSize * 10.f;
		float Y = Height / 3.f;

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
	}

	// All menu movement and events
	void STResolutionSettingsMenu::EventUpdate(const sf::Event& Event)
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
				bIsExit = true;
			}
			else if (Event.key.code == Button.EnterKey)
			{
				if (SelectedButton == 0)
				{
					ScreenWidth = 1280;
					ScreenHeight = 720;
				}
				else if (SelectedButton == 1)
				{
					ScreenWidth = 1920;
					ScreenHeight = 1080;
				}
				else if (SelectedButton == 2)
				{
					ScreenWidth = 2560;
					ScreenHeight = 1440;
				}

				bIsChosen = true;
			}
		}
	}

	void STResolutionSettingsMenu::Draw(sf::RenderWindow& Window)
	{
		for (auto& i : Buttons) {
			Window.draw(i);
		}
	}

	int STResolutionSettingsMenu::GetWidth() const
	{
		return ScreenWidth;
	}

	int STResolutionSettingsMenu::GetHeight() const
	{
		return ScreenHeight;
	}

	bool STResolutionSettingsMenu::IsExit() const
	{
		return bIsExit;
	}

	bool STResolutionSettingsMenu::IsChosen() const
	{
		return bIsChosen;
	}
	
	/*//////////////////////////////////*/
	/*                                  */
	/*	      PRIVATE WORKTOOLS         */
	/*                                  */
	/*//////////////////////////////////*/

	// Menu movement methods
	void STResolutionSettingsMenu::MoveUp()
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

	void STResolutionSettingsMenu::MoveDown()
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
}