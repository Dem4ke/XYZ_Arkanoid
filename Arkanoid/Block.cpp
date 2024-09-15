#include "Block.h"

namespace ArkanoidGame {
	Block::Block(Resources& resources, sf::RenderWindow& window) :
		resources_(resources), window_(window) {}

	void Block::init(float size, float speed, sf::Vector2f position) {
		height_ = size;
		width_ = size * 3.f;
		isCrashed_ = false;

		// Set shape's options
		SetRelativeOrigin(sprite_, 0.5f, 0.5f);
		position_ = position;
		sprite_.setPosition(position_.x, position_.y);
	}

	void Block::update(const float& deltaTime) {
		
	}

	void Block::draw() {
		window_.draw(sprite_);
	}
}