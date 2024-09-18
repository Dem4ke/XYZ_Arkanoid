#include "Ball.h"

namespace ArkanoidGame {

	Ball::Ball(Resources& resources, sf::RenderWindow& window) :
		resources_(resources), window_(window) {}

	void Ball::init(float size, float speed, sf::Vector2f position) {
		size_ = size;
		speed_ = speed;
		angle_ = -90.f;
		isOutOfPlayground_ = 0;

		// Set shape's options
		circle_.setRadius(size_ / 2.f);
		circle_.setFillColor(sf::Color::White);
		SetRelativeOrigin(circle_, 0.5f, 0.5f);

		// Set started direction of ball (unit vector)
		const float pi = std::acos(-1.f);
		direction_.x = std::cos(pi / 180.f * angle_);
		direction_.y = std::sin(pi / 180.f * angle_);

		// Set start position
		position_ = position;
		circle_.setPosition(position_.x, position_.y);
	}

	void Ball::update(const float& deltaTime) {
		// Calculate new position of ball
		position_ += (speed_ * deltaTime * direction_);	
		circle_.setPosition(position_);

		// Check collision with window's borders
		if (position_.x - size_ / 2.f < 0 || position_.x + size_ / 2.f > resources_.getWindowWidth()) {
			changeX();
		}
		
		if (position_.y - size_ / 2.f < 0) {
			changeY();
		}
		
		if (position_.y + size_ / 2.f > resources_.getWindowHeight()) {
			isOutOfPlayground_ = 1;
		}
	}

	void Ball::changeAngle(float newAngle) {
		// Change direction vector
		const auto pi = std::acos(-1.f);
		direction_.x = (newAngle / abs(newAngle)) * std::cos(pi / 180.f * newAngle);;
		direction_.y = -1 * abs(std::sin(pi / 180.f * newAngle));
	}

	void Ball::draw() {
		window_.draw(circle_);
	}

	void Ball::changeX() {
		direction_.x *= -1;
		HitSound(resources_);
	}

	void Ball::changeY() {
		direction_.y *= -1;
		HitSound(resources_);
	}

	int Ball::checkCollide(std::shared_ptr<GameObject> object) {
		return 0;
	}

	float Ball::getOriginX() const {
		return position_.x;
	}

	float Ball::getOriginY() const {
		return position_.y;
	}

	float Ball::getWidth() const {
		return size_;
	}

	float Ball::getHeight() const {
		return size_;
	}

	bool Ball::isOutOfPlayground() const { return isOutOfPlayground_; }
}