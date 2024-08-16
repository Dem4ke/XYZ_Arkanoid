#pragma once

#include "GameStates.h"
#include "Resources.h"

namespace ArkanoidGame {

	class UI {
	public:
		UI(Resources& resources, GameState& gameState, sf::RenderWindow& window);

		void init(float buttonSize);
		void scoreUpdate();
		void drawMain();
		void drawGameOver();

	private:
		sf::Text controlHelp_;
		sf::Text score_;
		sf::Text gameOverScore_;

		Resources& resources_;
		GameState& gameState_;
		sf::RenderWindow& window_;
	};
}
