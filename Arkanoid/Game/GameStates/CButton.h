#pragma once

#include <SFML/Graphics.hpp>

namespace Arkanoid
{
	// Struct which contains all buttons to work with application
	struct CButton
	{
	public:
		const sf::Keyboard::Key UpKey = sf::Keyboard::W;
		const sf::Keyboard::Key DownKey = sf::Keyboard::S;
		const sf::Keyboard::Key LeftKey = sf::Keyboard::A;
		const sf::Keyboard::Key RightKey = sf::Keyboard::D;
		const sf::Keyboard::Key EscapeKey = sf::Keyboard::End;
		const sf::Keyboard::Key EscapeKeyB = sf::Keyboard::B;
		const sf::Keyboard::Key EnterKey = sf::Keyboard::Enter;

		const sf::Color CommonColor = sf::Color::White;		// Color of all unchosen buttons
		const sf::Color ChosenColor = sf::Color::Blue;		// Color of a selected button
	};
}