#include <cassert>
#include "PauseState.h"
#include "../../GameStateObserver.h"
#include "../../../Settings/Settings.h"
#include "../../../Math/Math.h"

namespace Arkanoid
{
	void SPauseState::Init()
	{
		// Load sounds
		bool bIsLoaded = MovesSound.loadFromFile("Resources/Sounds/Owlstorm__Snake_hit.wav");
		assert(bIsLoaded);

		bIsLoaded = ChoiceSound.loadFromFile("Resources/Sounds/Theevilsocks__menu-hover.wav");
		assert(bIsLoaded);

		// Set clickable buttons for menu
		std::vector<std::string> InputButtons = { "Resume", "End game" };

		// Coordinates of menu items
		float Width = static_cast<float>(SETTINGS.GetScreenWidth());
		float Height = static_cast<float>(SETTINGS.GetScreenHeight());
		float X = Width / 2.f;
		float Y = Height / 3.f;

		// Initialization of a menu title
		MenuTitle.setFont(SETTINGS.GetResources()->GetFont());
		MenuTitle.setCharacterSize(TitleTextSize);
		MenuTitle.setFillColor(Button.CommonColor);
		MenuTitle.setString("Pause");
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
	void SPauseState::EventUpdate(const sf::Event& Event)
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
				ChangeGameplayType(PauseState::EPauseStateType::ContinueGame);
			}
			else if (Event.key.code == Button.EnterKey)
			{
				if (SelectedButton == 0)
				{
					ChangeGameplayType(PauseState::EPauseStateType::ContinueGame);
				}
				else if (SelectedButton == 1)
				{
					ChangeGameplayType(PauseState::EPauseStateType::ExitToMainMenu);
				}
			}
		}
	}

	void SPauseState::GameplayUpdate(const float DeltaTime) {}

	void SPauseState::Draw(sf::RenderWindow& Window)
	{
		Window.draw(MenuTitle);

		for (auto& i : Buttons) {
			Window.draw(i);
		}
	}

	void SPauseState::Attach(std::weak_ptr<IGameStateObserver> Observer)
	{
		Observers.push_back(Observer);
	}

	void SPauseState::Detach(std::weak_ptr<IGameStateObserver> Observer)
	{
		//Observers.erase(std::remove(Observers.begin(), Observers.end(), Observer.lock()), Observers.end());
	}

	void SPauseState::Notify(int NewGameStateType)
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
	void SPauseState::MoveUp()
	{
		if (SelectedButton >= 0)
		{
			Buttons[SelectedButton].setFillColor(Button.CommonColor);
			--SelectedButton;

			if (SelectedButton < 0)
			{
				SelectedButton = static_cast<int>(Buttons.size()) - 1;
			}

			Buttons[SelectedButton].setFillColor(Button.ChosenColor);
		}

		SETTINGS.GetResources()->PlaySound(MovesSound);
	}

	void SPauseState::MoveDown()
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

	// Method to change type of settings menu
	void SPauseState::ChangeGameplayType(PauseState::EPauseStateType NewType)
	{
		SETTINGS.GetResources()->PlaySound(ChoiceSound);
		Notify(static_cast<int>(NewType));
	}
}