#include "UI.h"

namespace ArkanoidGame {
	UI::UI(Resources& resources, GameState& gameState, sf::RenderWindow& window) :
		resources_(resources), gameState_(gameState), window_(window) {}

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
		gameOverScore_.setCharacterSize(buttonSize * 2.f);
		gameOverScore_.setFillColor(sf::Color::White);
		gameOverScore_.setString("Your score " + std::to_string(0));
		gameOverScore_.setPosition(resources_.getWindowWidth() / 2.f - gameOverScore_.getGlobalBounds().width / 2.f,
									resources_.getWindowHeight() / 4.f);
	}

	void UI::scoreUpdate() {
		score_.setString("Your score " + std::to_string(gameState_.getScore()));
		gameOverScore_.setString("Your score " + std::to_string(gameState_.getScore()));
		gameOverScore_.setString("Your score " + std::to_string(gameState_.getScore()));
	}

	// Draw UI in special cases
	void UI::drawMain() {
			window_.draw(controlHelp_);
			window_.draw(score_);
	}	

	void UI::drawGameOver() {
		window_.draw(gameOverScore_);
	}
}