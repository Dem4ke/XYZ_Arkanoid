#pragma once

#include "GameStates.h"
#include "Ball.h"
#include "Platform.h"

namespace ArkanoidGame {

	class GameField {
	public:
		GameField(Resources& resources, GameState& gameState, sf::RenderWindow& window);

		void init();
		void update(const float& deltaTime);
		void draw();

	private:
		Resources& resources_;
		GameState& gameState_;
		sf::RenderWindow& window_;

		Ball ball_;
		Platform platform_;

		sf::Sprite gameBackSprite_;
		sf::Color gameBackColor_ = sf::Color::Blue;
	};
}