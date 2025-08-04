#include <cassert>
#include "SoundSettingsMenuState.h"
#include "../GameStateObserver.h"
#include "../../Settings/Settings.h"
#include "../../Math/Math.h"

namespace Arkanoid
{
	void SSoundSettingsMenu::Init()
	{
		// Load sounds
		bool bIsLoaded = MovesSound.loadFromFile("Resources/Sounds/Owlstorm__Snake_hit.wav");
		assert(bIsLoaded);

		bIsLoaded = ChoiceSound.loadFromFile("Resources/Sounds/Theevilsocks__menu-hover.wav");
		assert(bIsLoaded);

		bIsSoundsOn = SETTINGS.IsSoundsOn();
		bIsMusicOn = SETTINGS.IsMusicOn();

		// Set clickable buttons for menu
		std::string SoundsText = bIsSoundsOn ? "Sounds : On" : "Sounds : Off";
		std::string MusicText = bIsMusicOn ? "Music : On" : "Music : Off";
		std::vector<std::string> InputButtons = { SoundsText, MusicText, "Apply", "Back" };

		// Coordinates of menu items
		float Width = static_cast<float>(SETTINGS.GetScreenWidth());
		float Height = static_cast<float>(SETTINGS.GetScreenHeight());
		float X = Width / 2.f;
		float Y = Height / 3.f;

		// Initialization of a menu title
		MenuTitle.setFont(SETTINGS.GetResources()->GetFont());
		MenuTitle.setCharacterSize(TitleTextSize);
		MenuTitle.setFillColor(Button.CommonColor);
		MenuTitle.setString("Sound settings");
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
	void SSoundSettingsMenu::EventUpdate(const sf::Event& Event)
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
				ChangeSettingsType(SoundSettingsMenu::ESettingsType::Main);
			}
			else if (Event.key.code == Button.EnterKey)
			{
				if (SelectedButton == 0)
				{
					bIsSoundsOn = !bIsSoundsOn;
					UpdateUi(SoundSettingsMenu::ESGUIType::Sounds);
				}
				else if (SelectedButton == 1)
				{
					bIsMusicOn = !bIsMusicOn;
					UpdateUi(SoundSettingsMenu::ESGUIType::Music);
				}
				else if (SelectedButton == 2)
				{
					SETTINGS.SetSoundsOn(bIsSoundsOn);

					if (SETTINGS.IsSoundsOn())
					{
						SETTINGS.GetResources()->SetSoundsVolume(5.f);
					}
					else
					{
						SETTINGS.GetResources()->SetSoundsVolume(0.f);
					}

					SETTINGS.SetMusicOn(bIsMusicOn);

					if (SETTINGS.IsMusicOn())
					{
						SETTINGS.GetResources()->PlayBackgroundMusic();
					}
					else
					{
						SETTINGS.GetResources()->StopBackgroundMusic();
					}

					SETTINGS.SaveSettings();
				}
				else if (SelectedButton == 3)
				{
					ChangeSettingsType(SoundSettingsMenu::ESettingsType::Main);
				}
			}
		}
	}

	void SSoundSettingsMenu::GameplayUpdate(const float DeltaTime) {}

	void SSoundSettingsMenu::Draw(sf::RenderWindow& Window)
	{
		Window.draw(MenuTitle);

		for (auto& i : Buttons) {
			Window.draw(i);
		}
	}

	void SSoundSettingsMenu::Attach(std::weak_ptr<IGameStateObserver> Observer)
	{
		Observers.push_back(Observer);
	}

	void SSoundSettingsMenu::Detach(std::weak_ptr<IGameStateObserver> Observer)
	{
		//Observers.erase(std::remove(Observers.begin(), Observers.end(), Observer.lock()), Observers.end());
	}

	void SSoundSettingsMenu::Notify(int NewGameStateType)
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

	// Menu movement methods
	void SSoundSettingsMenu::MoveUp()
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

	void SSoundSettingsMenu::MoveDown()
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

	void SSoundSettingsMenu::UpdateUi(SoundSettingsMenu::ESGUIType ChangedType)
	{
		SETTINGS.GetResources()->PlaySound(ChoiceSound);

		switch (ChangedType)
		{
		case SoundSettingsMenu::ESGUIType::Sounds:
		{
			std::string SoundsText = bIsSoundsOn ? "Sounds : On" : "Sounds : Off";
			Buttons[0].setString(SoundsText);
			break;
		}
		case SoundSettingsMenu::ESGUIType::Music:
		{
			std::string MusicText = bIsMusicOn ? "Music : On" : "Music : Off";
			Buttons[1].setString(MusicText);
			break;
		}
		}
	}

	// Method to change type of settings menu
	void SSoundSettingsMenu::ChangeSettingsType(SoundSettingsMenu::ESettingsType NewType)
	{		
		SETTINGS.GetResources()->PlaySound(ChoiceSound);
		Notify(static_cast<int>(NewType));
	}
}