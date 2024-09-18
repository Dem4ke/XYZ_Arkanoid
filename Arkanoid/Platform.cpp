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

	// Check is ball collide with platform and if it is, returns index, which coordinate axis must change
	int Platform::checkCollide(std::shared_ptr<GameObject> object) {
		float xNormal = object->getHeight() + 1.f;
		float yNormal = object->getHeight() + 1.f;

		// Search area of triangle between ball's origin and platform's side
		auto triangleArea = [](float x1, float y1, float x2, float y2, float x3, float y3) {
			return std::fabs((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1)) / 2.f;
		};

		// Search length of platform's side
		auto baseLength = [](float x1, float y1, float x2, float y2) {
			return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
		};

		// Search normal from ball's orifin to platform's side
		auto triangleHeight = [](float triangleArea, float baseLenght) {
			return triangleArea * 2.f / baseLenght;
		};

		if ((object->getOriginX() + object->getWidth() / 3.f > getOriginX() - getWidth() / 2.f) &&
			(object->getOriginX() - object->getWidth() / 3.f < getOriginX() + getWidth() / 2.f)) {

			float area1 = triangleArea(object->getOriginX(), object->getOriginY(),
				getOriginX() - getWidth() / 2.f, getOriginY() + getHeight() / 2.f,
				getOriginX() + getWidth() / 2.f, getOriginY() + getHeight() / 2.f);

			float area2 = triangleArea(object->getOriginX(), object->getOriginY(),
				getOriginX() - getWidth() / 2.f, getOriginY() - getHeight() / 2.f,
				getOriginX() + getWidth() / 2.f, getOriginY() - getHeight() / 2.f);

			float length = baseLength(getOriginX() - getWidth() / 2.f, getOriginY() + getHeight() / 2.f,
				getOriginX() + getWidth() / 2.f, getOriginY() + getHeight() / 2.f);

			yNormal = area1 < area2 ? triangleHeight(area1, length) : triangleHeight(area2, length);
		}

		if (yNormal < object->getWidth() / 2.f) {
			return 1;
		}

		return 0;
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