#include "Wall.h"

namespace SnakeGame {

	// ROCK INITIALIZATION

	//void Rock::init(float size) {
	//	size_ = size;
	//	position_ = GetRandomPositionInScreen(resources_.getWindowWidth(), resources_.getWindowHeight());

	//	sprite_.setTexture(resources_.rockTexture);
	//	sprite_.setPosition(position_.x, position_.y);

	//	SetSpriteSize(sprite_, size_, size_);
	//	SetSpriteRelativeOrigin(sprite_, 0.5f, 0.5f);
	//}

	//float Rock::getSize() const { return size_; }

	//sf::Sprite Rock::getSprite() const { return sprite_; }

	//// FUNCTIONS

	//// Initialization of array of rocks, take one Rock class object and make array of them
	//void RocksFieldInit(Rock& rock, std::vector<Rock>& fieldOfRocks, float size, int num) {
	//	// Clear field
	//	fieldOfRocks.clear();
	//	// Init new field
	//	for (int i = 0; i < num; ++i) {
	//		rock.init(size);
	//		fieldOfRocks.push_back(rock);
	//	}
	//}

	//// Check player collision with any rock
	//void RockCollision(std::vector<Rock>& fieldOfRocks, Player& player, Resources& resources, GameStates& settings) {
	//	for (auto& rock : fieldOfRocks) {
	//		if (IsCircusCollide(player.position_, player.getSize(), rock.position_, rock.getSize())) {

	//			GameOverSound(resources);
	//			pushGameState(settings, GameStateType::GameOver);
	//		}
	//	}
	//}

	//// Draw rocks
	//void DrawRocks(std::vector<Rock>& fieldOfRocks, sf::RenderWindow& window) {
	//	for (auto& rock : fieldOfRocks) {
	//		window.draw(rock.getSprite());
	//	}
	//}
}