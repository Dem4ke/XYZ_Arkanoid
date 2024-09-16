#include "Platform.h"

namespace ArkanoidGame {

	// PLATFORM INITIALIZATION

	Platform::Platform(Resources& resources, sf::RenderWindow& window) :
		resources_(resources), window_(window) {}

	void Platform::init(float size, float speed, sf::Vector2f position) {
		width_ = size;
		speed_ = speed;

		rectangle_.setSize(sf::Vector2f(width_, height_));
		rectangle_.setFillColor(sf::Color::Cyan);
		SetRelativeOrigin(rectangle_, 0.5f, 0.5f);

		position_ = position;
		rectangle_.setPosition(position_.x, position_.y);
	}

	void Platform::update(const float& deltaTime) {
		// Change velocity direction of platform while player pressed key
		if (sf::Keyboard::isKeyPressed(rightKey_)) {
			if ((position_.x + rectangle_.getSize().x / 2.f) >= resources_.getWindowWidth()) {
				// Stop platform
				position_.x += speed_ * 0;
			}
			else {
				// Platform goes to right
				position_.x += speed_ * deltaTime;
			}
		}
		else if (sf::Keyboard::isKeyPressed(leftKey_)) {
			if ((position_.x - rectangle_.getSize().x / 2.f) <= 0) {
				// Stop platform
				position_.x += speed_ * 0;
			}
			else {
				// Platform goes to left
				position_.x -= speed_ * deltaTime;
			}
		}

		// Update platform's position
		rectangle_.setPosition(position_.x, position_.y);
	}

	void Platform::draw() {
		window_.draw(rectangle_);
	}

	float Platform::getOriginX() const {
		return position_.x;
	}

	float Platform::getOriginY() const {
		return position_.y;
	}

	float Platform::getWidth() const {
		return width_;
	}

	float Platform::getHeight() const {
		return height_;
	}
}