#include <cassert>
#include "VideoSettingsMenuState.h"
#include "ResolutionSettingsMenu.h"
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

		bIsFullscreenOn = SETTINGS.IsFullscreenMode();
		ScreenWidth = SETTINGS.GetScreenWidth();
		ScreenHeight = SETTINGS.GetScreenHeight();

		// Set clickable buttons for menu
		std::string FullscreenText = bIsFullscreenOn ? "Fullscreen: Yes" : "Fullscreen: No";
		std::string ResolutionText = "Resolution: " + std::to_string(ScreenWidth) + " x " + std::to_string(ScreenHeight);
		std::vector<std::string> InputButtons = { FullscreenText, ResolutionText, "Apply", "Back"};

		// Coordinates of menu items
		float Width = static_cast<float>(SETTINGS.GetScreenWidth());
		float Height = static_cast<float>(SETTINGS.GetScreenHeight());
		float X = Width / 2.f;
		float Y = Height / 3.f;


		// Initialization of a menu title
		MenuTitle.setFont(SETTINGS.GetResources()->GetFont());
		MenuTitle.setCharacterSize(TitleTextSize);
		MenuTitle.setFillColor(Button.CommonColor);
		MenuTitle.setString("Video settings");
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
	}

	// All menu movement and events
	void STVideoSettingMenu::EventUpdate(const sf::Event& Event)
	{
		if (bIsResolutionsSnow)
		{
			Resolution->EventUpdate(Event);
			
			if (Resolution->IsChosen())
			{
				ScreenWidth = Resolution->GetWidth();
				ScreenHeight = Resolution->GetHeight();

				UpdateUi(EVGUIType::Resolution);
				bIsResolutionsSnow = false;
			}
			else if (Resolution->IsExit())
			{
				bIsResolutionsSnow = false;
			}
		}
		else 
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
						bIsFullscreenOn = !bIsFullscreenOn;
						UpdateUi(EVGUIType::FullscreenMode);
					}
					else if (SelectedButton == 1)
					{
						bIsResolutionsSnow = !bIsResolutionsSnow;

						if (bIsResolutionsSnow)
						{
							if (Resolution)
							{
								Resolution = nullptr;
							}

							Resolution = std::make_shared<STResolutionSettingsMenu>();
						}
					}
					else if (SelectedButton == 2)
					{
						if (bIsFullscreenOn != SETTINGS.IsFullscreenMode())
						{
							bIsFullscreenModeChanged = true;
							SETTINGS.SetFullscreenMode(bIsFullscreenOn);
						}

						if (ScreenWidth != SETTINGS.GetScreenWidth() && ScreenHeight != SETTINGS.GetScreenHeight())
						{
							bIsResolutionChanged = true;
							SETTINGS.SetScreenWidth(ScreenWidth);
							SETTINGS.SetScreenHeight(ScreenHeight);
						}

						SETTINGS.SaveSettings();
					}
					else if (SelectedButton == 3)
					{
						ChangeSettingsType(ESettingsType::Main);
					}
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

		if (bIsResolutionsSnow)
		{
			Resolution->Draw(Window);
		}

		if (bIsFullscreenModeChanged)
		{
			unsigned int WIndowWidth = SETTINGS.GetScreenWidth();
			unsigned int WIndowHeight = SETTINGS.GetScreenHeight();
			sf::Uint32 Style = SETTINGS.IsFullscreenMode() ? sf::Style::Fullscreen : sf::Style::Default;
			Window.create(sf::VideoMode(WIndowWidth, WIndowHeight), "Arkanoid!", Style);

			bIsFullscreenModeChanged = false;
			ChangeSettingsType(ESettingsType::Main);
		}

		if (bIsResolutionChanged)
		{
			unsigned int WIndowWidth = SETTINGS.GetScreenWidth();
			unsigned int WIndowHeight = SETTINGS.GetScreenHeight();
			sf::Uint32 Style = SETTINGS.IsFullscreenMode() ? sf::Style::Fullscreen : sf::Style::Default;
			Window.create(sf::VideoMode(WIndowWidth, WIndowHeight), "Arkanoid!", Style);

			bIsResolutionChanged = false;
			ChangeSettingsType(ESettingsType::Main);
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

	void STVideoSettingMenu::MoveDown()
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

	void STVideoSettingMenu::UpdateUi(EVGUIType ChangedType)
	{
		SETTINGS.GetResources()->PlaySound(ChoiceSound);

		switch (ChangedType)
		{
		case EVGUIType::FullscreenMode:
		{
			std::string FullscreenText = bIsFullscreenOn ? "Fullscreen: Yes" : "Fullscreen: No";
			Buttons[0].setString(FullscreenText);
			break;
		}
		case EVGUIType::Resolution:
		{
			std::string ResolutionText = "Resolution: " + std::to_string(ScreenWidth) + " x " + std::to_string(ScreenHeight);
			Buttons[1].setString(ResolutionText);
			break;
		}
		}
	}

	// Method to change type of settings menu
	void STVideoSettingMenu::ChangeSettingsType(ESettingsType NewType)
	{
		bIsSettingsTypeUpdated = true;
		SettingsType = NewType;

		SETTINGS.GetResources()->PlaySound(ChoiceSound);
	}
}