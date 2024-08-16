#include "Platform.h"

namespace ArkanoidGame {

	// PLATFORM INITIALIZATION

	Platform::Platform(Resources& resources, sf::RenderWindow& window) : 
	resources_(resources), window_(window) {}

	void Platform::init(int width, float speed) {
		direction_ = PlatformDirection::None;

		width_ = width;
		speed_ = speed;

		rectangle_.setSize(sf::Vector2f(width_, height_));
		rectangle_.setFillColor(sf::Color::Cyan);
		SetRectangleRelativeOrigin(rectangle_, 0.5f, 0.5f);

		position_ = { resources_.getWindowWidth() / 2.f, resources_.getWindowHeight() - height_ };
		rectangle_.setPosition(position_.x, position_.y);
	}

	void Platform::move(const float& deltaTime) {
		// Change dirertion of platform
		if (sf::Keyboard::isKeyPressed(rightKey_)) {
			if ((position_.x + rectangle_.getSize().x / 2.f) >= resources_.getWindowWidth()) {
				direction_ = PlatformDirection::None;
			}
			else {
				direction_ = PlatformDirection::Right;
			}
		}
		else if (sf::Keyboard::isKeyPressed(leftKey_)) {
			if ((position_.x - rectangle_.getSize().x / 2.f) <= 0) {
				direction_ = PlatformDirection::None;
			}
			else {
				direction_ = PlatformDirection::Left;
			}	
		}

		// Change platform's "speed" direction 
		switch (direction_) {
		case PlatformDirection::None: {
			position_.x += speed_ * 0;
			break;
		}
		case PlatformDirection::Right: {
			position_.x += speed_ * deltaTime;
			break;
		}
		case PlatformDirection::Left: {
			position_.x -= speed_ * deltaTime;
			break;
		}
		}

		// Update platform's position
		rectangle_.setPosition(position_.x, position_.y);

		// Check collision with window's borders
		if ((position_.x + rectangle_.getSize().x / 2.f) >= resources_.getWindowWidth() ||
			(position_.x - rectangle_.getSize().x / 2.f) <= 0) {
		
			direction_ = PlatformDirection::None;
		}
	}

	void Platform::draw() {
		window_.draw(rectangle_);
	}
}