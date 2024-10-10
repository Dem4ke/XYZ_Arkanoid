#include "GameField.h"


namespace ArkanoidGame {
	GameField::GameField(Resources& resources, GameState& gameState, sf::RenderWindow& window) :
		resources_(resources), gameState_(gameState), window_(window) {}

	void GameField::init() {
		// Initialization of player's platform (width, speed, position on screen)
		switch (gameState_.getCurrentDiffLvl()) {
		case DifficultyLevel::Easy: {
			// Platform initialization
			objects_.emplace_back(std::make_shared<Platform>(resources_, window_));
			objects_[0]->init(140.f, 600.f, sf::Vector2f(resources_.getWindowWidth() / 2.f, resources_.getWindowHeight() - 20.f));
			break;
		}
		case DifficultyLevel::Medium: {
			objects_.emplace_back(std::make_shared<Platform>(resources_, window_));
			objects_[0]->init(120.f, 600.f, sf::Vector2f(resources_.getWindowWidth() / 2.f, resources_.getWindowHeight() - 20.f));
			break;
		}
		case DifficultyLevel::Hard: {
			objects_.emplace_back(std::make_shared<Platform>(resources_, window_));
			objects_[0]->init(100.f, 600.f, sf::Vector2f(resources_.getWindowWidth() / 2.f, resources_.getWindowHeight() - 20.f));
			break;
		}
		}

		// Initialization of ball (size, speed, position on screen)
		objects_.emplace_back(std::make_shared<Ball>(resources_, window_));
		objects_[1]->init(20.f, 500.f, sf::Vector2f(resources_.getWindowWidth() / 2.f, resources_.getWindowHeight() - 40.f));

		// Initialization of blocks (height (widht will be in 3 times bigger), speed = 0, position on screen)
		for (int i = 0; i < 8; ++i) {
			blocks_.emplace_back(std::make_shared<Block>(resources_, window_));
			blocks_[i]->init(20.f, 0, sf::Vector2f(i * 100.f + 40.f, 60.f));
		}
		for (int i = 0; i < 6; ++i) {
			blocks_.emplace_back(std::make_shared<Block>(resources_, window_));
			blocks_[i + 8]->init(20.f, 0, sf::Vector2f(i * 120.f + 100.f, 100.f));
		}
		for (int i = 0; i < 8; ++i) {
			blocks_.emplace_back(std::make_shared<Block>(resources_, window_));
			blocks_[i + 14]->init(20.f, 0, sf::Vector2f(i * 100.f + 40.f, 140.f));
		}

		// Initialization of background of the game
		gameBackSprite_.setTexture(resources_.gameBackground);
		SetSize(gameBackSprite_, resources_.getWindowWidth(), resources_.getWindowHeight());
		gameBackSprite_.setColor(gameBackColor_);
	}

	void GameField::reset() {
		objects_.clear();
		blocks_.clear();
		init();
	}

	void GameField::update(const float& deltaTime) {
		// All game objects updates
		static auto updateFunctor = [deltaTime](auto obj) { 
			obj->update(deltaTime); 
		};

		std::for_each(objects_.begin(), objects_.end(), updateFunctor);
		std::for_each(blocks_.begin(), blocks_.end(), updateFunctor);

		std::shared_ptr<Platform> platform = std::static_pointer_cast<Platform>(objects_[0]);
		std::shared_ptr<Ball> ball = std::static_pointer_cast<Ball>(objects_[1]);

		// Check collision between ball and blocks
		for (int i = 0; i < blocks_.size(); ++i) {
			if (blocks_[i]->checkCollide(ball) == 1) {
				ball->needToChangeY();
				blocks_.erase(blocks_.cbegin() + i);

				gameState_.scoreIncrease(1);
			}
			else if (blocks_[i]->checkCollide(ball) == 2) {
				ball->needToChangeX();
				blocks_.erase(blocks_.cbegin() + i);

				gameState_.scoreIncrease(1);
			}
		}

		switch (ball->changedWay()) {
		case 1: {
			ball->changeY();
			break;
		}
		case 2: {
			ball->changeX();
			break;
		}
		}

		// Check collision between ball and platform
		if (platform->checkCollide(ball) == 1) {
			// Find relative place of collide (-1 is left corner, 1 is right corner)
			float collidePlace = (ball->getOriginX() - platform->getOriginX()) / platform->getWidth() / 2;

			float newAngle = 90.f - 120.f * collidePlace;
			ball->changeAngle(newAngle);
			HitSound(resources_);
		}

		// Check is ball in playground
		else if (ball->isOutOfPlayground()) {
			gameState_.pushGameState(GameStateType::GameOverPopUp);
			GameOverSound(resources_);
		}

		// Check is blocks over
		if (blocks_.size() == 0) {
			gameState_.pushGameState(GameStateType::GameWinPopUp);
			GameWinSound(resources_);
		}
	}

	void GameField::draw() {
		window_.draw(gameBackSprite_);

		static auto drawFunctor = [](auto obj) {
			obj->draw();
		};

		std::for_each(objects_.begin(), objects_.end(), drawFunctor);
		std::for_each(blocks_.begin(), blocks_.end(), drawFunctor);
	}
}