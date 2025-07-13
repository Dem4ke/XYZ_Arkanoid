#include "GameUI.h"
#include "../../../Settings/Settings.h"

namespace Arkanoid
{
	OGameUI::OGameUI()
	{
		// Coordinates of UI items
		float Width = static_cast<float>(SETTINGS.GetScreenWidth());
		float Height = static_cast<float>(SETTINGS.GetScreenHeight());
		float X = 20.f;
		float Y = Height - TextSize;

		// Set text of UI items and add them in vector
		sf::Text Input;
		Input.setFont(SETTINGS.GetResources()->GetFont());
		Input.setCharacterSize(TextSize);
		Input.setFillColor(sf::Color::White);
		Input.setString("Score: 0");
		Input.setOrigin(sf::Vector2f(0, Input.getGlobalBounds().height / 2.f));
		Input.setPosition(X, Y);
		Text.push_back(Input);

		X = Width - 60.f;
		Input.setString("Lifes: 0");
		Input.setOrigin(sf::Vector2f(Input.getGlobalBounds().width, Input.getGlobalBounds().height / 2.f));
		Input.setPosition(X, Y);
		Text.push_back(Input);
	}

	void OGameUI::SetScore(int Value)
	{
		Text[0].setString("Score: " + std::to_string(Value));
	}

	void OGameUI::SetBallLifes(int Value)
	{
		Text[1].setString("Lifes: " + std::to_string(Value));
	}

	void OGameUI::Draw(sf::RenderWindow& Window)
	{
		for (auto& i : Text) {
			Window.draw(i);
		}
	}
}