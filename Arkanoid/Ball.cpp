#include "Ball.h"

namespace ArkanoidGame {

	Ball::Ball(Resources& resources, sf::RenderWindow& window) :
		resources_(resources), window_(window) {}

	void Ball::init(float size, float speed) {
		size_ = size;
		speed_ = speed;

		rectangle_.setSize(sf::Vector2f(size_, size_));
		rectangle_.setFillColor(sf::Color::White);
		SetRectangleRelativeOrigin(rectangle_, 0.5f, 0.5f);

		position_ = { resources_.getWindowWidth() / 2.f, resources_.getWindowHeight() - 40.f };
		rectangle_.setPosition(position_.x, position_.y);
	}

	void Ball::move(const float& deltaTime) {
	
	}

	void Ball::draw() {
		window_.draw(rectangle_);
	}
}