#include <cassert>
#include "LeaderBoard.h"
#include "LeaderBoardMenuState.h"
#include "../GameStateObserver.h"
#include "../../Settings/Settings.h"
#include "../../Math/Math.h"

namespace Arkanoid
{
	void SLeaderBoardMenu::Init()
	{
		// Load textures
		bool bIsLoaded = BackgroundTexture.loadFromFile("Resources/Backgrounds/Menu_background.jpg");
		assert(bIsLoaded);

		// Load sounds
		bIsLoaded = MovesSound.loadFromFile("Resources/Sounds/Owlstorm__Snake_hit.wav");
		assert(bIsLoaded);

		bIsLoaded = ChoiceSound.loadFromFile("Resources/Sounds/Theevilsocks__menu-hover.wav");
		assert(bIsLoaded);

		// Coordinates of menu items
		float Width = static_cast<float>(SETTINGS.GetScreenWidth());
		float Height = static_cast<float>(SETTINGS.GetScreenHeight());
		float X = Width / 2.f;
		float Y = Height / 7.f;

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

		// Initialization of the exit button
		ExitButton.setFont(SETTINGS.GetResources()->GetFont());
		ExitButton.setCharacterSize(ButtonsTextSize);
		ExitButton.setFillColor(Button.CommonColor);
		ExitButton.setString("Exit");
		ExitButton.setOrigin(sf::Vector2f(ExitButton.getGlobalBounds().width / 2.f, ExitButton.getGlobalBounds().height / 2.f));
		ExitButton.setPosition(X, Height - Height / 10.f);
		ExitButton.setFillColor(Button.ChosenColor);

		// Get information from leader board file
		ULeaderBoard LeaderBoard;
		std::vector<std::pair<std::string, int>> InputLeaderBoard = LeaderBoard.GetTable();

		// Initialization of the leader board
		float space = static_cast<float> (ButtonsTextSize);

		sf::Text PlayerName;
		sf::Text PlayerScore;

		PlayerName.setFont(SETTINGS.GetResources()->GetFont());
		PlayerName.setCharacterSize(ButtonsTextSize);
		PlayerName.setFillColor(Button.CommonColor);

		PlayerScore.setFont(SETTINGS.GetResources()->GetFont());
		PlayerScore.setCharacterSize(ButtonsTextSize);
		PlayerScore.setFillColor(Button.CommonColor);

		int PlayersToDraw = 0; // Counter to check how many players have added
		Table.clear();

		for (auto& i : InputLeaderBoard) {
			PlayerName.setString(i.first);
			PlayerName.setOrigin(sf::Vector2f(PlayerName.getGlobalBounds().width / 2.f, PlayerName.getGlobalBounds().height / 2.f));
			PlayerName.setPosition(X - ButtonsTextSize * 1.5f, Y + space * 1.2f);

			PlayerScore.setString(std::to_string(i.second));
			PlayerScore.setOrigin(sf::Vector2f(0.f, PlayerName.getGlobalBounds().height / 2.f));
			PlayerScore.setPosition(X + ButtonsTextSize * 2.5f, Y + space * 1.2f);

			Table.push_back({ PlayerName, PlayerScore });
			space += ButtonsTextSize;
			++PlayersToDraw;

			if (PlayersToDraw == DrawablePlayers)
			{
				break;
			}
		}
	}

	// All menu movement and events
	void SLeaderBoardMenu::EventUpdate(const sf::Event& Event)
	{
		if (Event.type == sf::Event::KeyReleased)
		{
			if (Event.key.code == Button.EscapeKey || Event.key.code == Button.EscapeKeyB)
			{
				SetNewGameState(LeaderBoardMenu::EGameStateType::MainMenu);
			}
			else if (Event.key.code == Button.EnterKey)
			{
				SetNewGameState(LeaderBoardMenu::EGameStateType::MainMenu);
			}
		}
	}

	void SLeaderBoardMenu::GameplayUpdate(const float DeltaTime) {}

	void SLeaderBoardMenu::Draw(sf::RenderWindow& Window)
	{
		Window.draw(BackgroundSprite);
		Window.draw(MenuTitle);
		Window.draw(ExitButton);

		for (auto& i : Table) {
			Window.draw(i.first);
			Window.draw(i.second);
		}
	}

	void SLeaderBoardMenu::Attach(std::weak_ptr<IGameStateObserver> Observer)
	{
		Observers.push_back(Observer);
	}

	void SLeaderBoardMenu::Detach(std::weak_ptr<IGameStateObserver> Observer)
	{
		Observers.erase(std::remove(Observers.begin(), Observers.end(), Observer.lock()), Observers.end());
	}

	void SLeaderBoardMenu::Notify(int NewGameStateType)
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

	// Change flag and state type 
	void SLeaderBoardMenu::SetNewGameState(LeaderBoardMenu::EGameStateType NewState)
	{
		SETTINGS.GetResources()->PlaySound(ChoiceSound);
		Notify(static_cast<int>(NewState));
	}
}