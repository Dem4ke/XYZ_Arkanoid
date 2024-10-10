#pragma once

#include "GameStates.h"
#include "Ball.h"
#include "Block.h"
#include "Platform.h"

namespace ArkanoidGame {

	class GameField {
	public:
		GameField(Resources& resources, GameState& gameState, sf::RenderWindow& window);

		void init();
		void reset();
		void update(const float& deltaTime);
		void draw();

	private:
		Resources& resources_;
		GameState& gameState_;
		sf::RenderWindow& window_;

		std::vector<std::shared_ptr<GameObject>> objects_;
		std::vector<std::shared_ptr<Block>> blocks_;

		sf::Sprite gameBackSprite_;
		sf::Color gameBackColor_ = sf::Color::Blue;
	};
}