#pragma once

#include "GameStates.h"
#include "Resources.h"

namespace SnakeGame {

	class UI {
	public:
		UI(Resources& resources) : resources_(resources) {}
		void init(float buttonSize);
		void scoreUpdate(GameState& gameStates);

		sf::Text getHelp() const;
		sf::Text getScore() const;
		sf::Text getGameOverScore() const;
	private:
		sf::Text controlHelp_;
		sf::Text score_;
		sf::Text gameOverScore_;

		Resources& resources_;
	};

	void DrawUI(UI& UI, sf::RenderWindow& window);
	void DrawGameOverUI(UI& UI, sf::RenderWindow& window);
}
