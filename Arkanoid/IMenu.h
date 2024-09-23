#pragma once

#include <SFML/Graphics.hpp>
#include "GameStates.h"

namespace ArkanoidGame {
	class IMenu {
	public:
		virtual ~IMenu() = default;

		virtual void init() = 0;
		virtual void reset() = 0;
		virtual void update(const sf::Event& event) = 0;
		virtual void draw() = 0;

		virtual GameStateType getState() = 0;

	protected:
		sf::Sprite backgroundSprite_;

		sf::Keyboard::Key upKey_ = sf::Keyboard::W;
		sf::Keyboard::Key downKey_ = sf::Keyboard::S;
		sf::Keyboard::Key leftKey_ = sf::Keyboard::A;
		sf::Keyboard::Key rightKey_ = sf::Keyboard::D;
		sf::Keyboard::Key escapeKey_ = sf::Keyboard::B;
		sf::Keyboard::Key enterKey_ = sf::Keyboard::Enter;
	};
}