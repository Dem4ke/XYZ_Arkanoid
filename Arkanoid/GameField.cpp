#include "GameField.h"


namespace ArkanoidGame {
	GameField::GameField(Resources& resources, GameState& gameState, sf::RenderWindow& window) :
		resources_(resources), gameState_(gameState), window_(window) {}

	GameField::~GameField() {}

	void GameField::init() {
		// Initialization of player's platform (width, speed) 
		// Initialization of ball (size, speed)
		switch (gameState_.getCurrentDiffLvl()) {
		case DifficultyLevel::Easy: {
			// Platform initialization
			objects_.emplace_back(std::make_shared<Platform>(resources_, window_));
			objects_[0]->init(140.f, 700.f, sf::Vector2f(resources_.getWindowWidth() / 2.f, resources_.getWindowHeight() - 20.f));
			break;
		}
		case DifficultyLevel::Medium: {
			objects_.emplace_back(std::make_shared<Platform>(resources_, window_));
			objects_[0]->init(120.f, 700.f, sf::Vector2f(resources_.getWindowWidth() / 2.f, resources_.getWindowHeight() - 20.f));
			break;
		}
		case DifficultyLevel::Hard: {
			objects_.emplace_back(std::make_shared<Platform>(resources_, window_));
			objects_[0]->init(100.f, 700.f, sf::Vector2f(resources_.getWindowWidth() / 2.f, resources_.getWindowHeight() - 20.f));
			break;
		}
		}

		// Ball initialization
		objects_.emplace_back(std::make_shared<Ball>(resources_, window_));
		objects_[1]->init(20.f, 600.f, sf::Vector2f(resources_.getWindowWidth() / 2.f, resources_.getWindowHeight() - 40.f));

		// Blocks initialization
		for (int i = 0; i < 10; ++i) {
			blocks_.emplace_back(std::make_shared<Block>(resources_, window_));
			blocks_[i]->init(20.f, 0, sf::Vector2f(i * 80.f, 60.f));
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

		std::shared_ptr <Platform> platform = std::static_pointer_cast<Platform>(objects_[0]);
		std::shared_ptr<Ball> ball = std::static_pointer_cast<Ball>(objects_[1]);
		
		// Check collision between ball and platform
		if (IsCircleAndRectangleCollide(ball->getSize() / 2.f, ball->centerX(), ball->bottomY(), 
										platform->topLeftX(), platform->topRightX(), platform->topY())) {
			// Find relative place of collide (-1 is left corner, 1 is right corner)
			float collidePlace = (ball->centerX() - (platform->topLeftX() + platform->getWidth() / 2)) / platform->getWidth() / 2;

			float newAngle = 90.f - 120.f * collidePlace;
			ball->changeAngle(newAngle);
			HitSound(resources_);
		}

		// Check is ball in playground
		else if (ball->isOutOfPlayground()) {
			gameState_.pushGameState(GameStateType::GameOverPopUp);
			GameOverSound(resources_);
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