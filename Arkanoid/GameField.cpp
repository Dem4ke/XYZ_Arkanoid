#include "GameField.h"

namespace ArkanoidGame {
	GameField::GameField(Resources& resources, GameState& gameState, sf::RenderWindow& window) :
		resources_(resources), gameState_(gameState), window_(window), 
		ball_(resources, window), platform_(resources, window) {}

	void GameField::init() {
		// Initialization of player's platform (width, speed) 
		// Initialization of ball (size, speed)
		switch (gameState_.getCurrentDiffLvl()) {
		case DifficultyLevel::Easy: {
			platform_.init(140, 500.f);
			ball_.init();
			break;
		}
		case DifficultyLevel::Medium: {
			platform_.init(100, 550.f);
			ball_.init();
			break;
		}
		case DifficultyLevel::Hard: {
			platform_.init(60, 600.f);
			ball_.init();
			break;
		}
		}

		// Initialization of background of the game
		gameBackSprite_.setTexture(resources_.gameBackground);
		SetSize(gameBackSprite_, resources_.getWindowWidth(), resources_.getWindowHeight());
		gameBackSprite_.setColor(gameBackColor_);
	}

	void GameField::update(const float& deltaTime) {
		// Platform and ball movement
		platform_.move(deltaTime);
		ball_.move(deltaTime);
		
		// Check collision between ball and platform
		if (IsCircleAndRectangleCollide(ball_.getSize() / 2.f, ball_.centerX(), ball_.bottomY(), 
										platform_.topLeftX(), platform_.topRightX(), platform_.topY())) {
			// Find relative place of collide (-1 is left corner, 1 is right corner)
			float collidePlace = ball_.centerX() < platform_.centerX() ? 
							   - ball_.centerX() / (platform_.topLeftX() + platform_.centerX()) :
								 ball_.centerX() / (platform_.centerX() + platform_.topRightX());


			float newAngle = 90 - 20 * collidePlace;
			ball_.changeAngle(newAngle);
			HitSound(resources_);
		}

		// Check is ball in playground
		else if (ball_.isOutOfPlayground()) {
			gameState_.pushGameState(GameStateType::GameOverPopUp);
			GameOverSound(resources_);
		}
	}

	void GameField::draw() {
		window_.draw(gameBackSprite_);

		platform_.draw();
		ball_.draw();
	}
}