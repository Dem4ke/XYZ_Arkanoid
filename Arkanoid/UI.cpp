#include "UI.h"

namespace SnakeGame {
	void UI::init(float buttonSize) {
		// Initialization of conrtol help
		controlHelp_.setFont(resources_.font);
		controlHelp_.setCharacterSize(buttonSize);
		controlHelp_.setFillColor(sf::Color::White);
		controlHelp_.setString("Use WASD to move, P to pause");
		controlHelp_.setPosition(controlHelp_.getGlobalBounds().width - controlHelp_.getGlobalBounds().width / 1.1f,
			controlHelp_.getGlobalBounds().height);

		// Initialization of player score
		score_.setFont(resources_.font);
		score_.setCharacterSize(buttonSize);
		score_.setFillColor(sf::Color::White);
		score_.setString("Your score " + std::to_string(0));
		score_.setPosition(resources_.getWindowWidth() - score_.getGlobalBounds().width * 1.5f,
			score_.getGlobalBounds().height);

		// Initialization of player score in game over menu
		gameOverScore_.setFont(resources_.font);
		gameOverScore_.setCharacterSize(buttonSize * 2);
		gameOverScore_.setFillColor(sf::Color::White);
		gameOverScore_.setString("Your score " + std::to_string(0));
		gameOverScore_.setPosition(resources_.getWindowWidth() / 2.f - gameOverScore_.getGlobalBounds().width / 2.f,
									resources_.getWindowHeight() / 4.f);
	}

	void UI::scoreUpdate(GameState& gameStates) {
		score_.setString("Your score " + std::to_string(gameStates.getScore()));
		gameOverScore_.setString("Your score " + std::to_string(gameStates.getScore()));
		gameOverScore_.setString("Your score " + std::to_string(gameStates.getScore()));
	}

	sf::Text UI::getHelp() const { return controlHelp_; }

	sf::Text UI::getScore() const { return score_; }

	sf::Text UI::getGameOverScore() const { return gameOverScore_; }

	// FUNCTIONS

	void DrawUI(UI& UI, sf::RenderWindow& window) {
		window.draw(UI.getHelp());
		window.draw(UI.getScore());
	}
	void DrawGameOverUI(UI& UI, sf::RenderWindow& window) {
		window.draw(UI.getGameOverScore());
	}
}