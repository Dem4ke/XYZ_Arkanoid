#pragma once

#include <SFML/Graphics.hpp>

namespace ArkanoidGame {
	class GameStatesData {
	public:
		virtual ~GameStatesData() = default;

		virtual void init() = 0;
		virtual void reset() = 0;
		virtual void update(const sf::Event& event) = 0;
		virtual void draw() = 0;

	protected:
		virtual void moveUp() = 0;
		virtual void moveDown() = 0;

		int selectedButton_ = 0;

		std::vector<sf::Text> buttons_;
		sf::Text menuName_;

		sf::Color mainButtonColor_ = sf::Color::White;
		sf::Color chosenButtonColor_ = sf::Color::Blue;

		sf::Sprite backgroundSprite_;

		sf::Keyboard::Key upKey_ = sf::Keyboard::W;
		sf::Keyboard::Key downKey_ = sf::Keyboard::S;
		sf::Keyboard::Key leftKey_ = sf::Keyboard::A;
		sf::Keyboard::Key rightKey_ = sf::Keyboard::D;
		sf::Keyboard::Key escapeKey_ = sf::Keyboard::B;
		sf::Keyboard::Key enterKey_ = sf::Keyboard::Enter;
	};
}