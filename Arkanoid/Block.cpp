#include "Block.h"

namespace ArkanoidGame {
	Block::Block(Resources& resources, sf::RenderWindow& window) :
		resources_(resources), window_(window) {}

	void Block::init(float size, float speed, sf::Vector2f position) {
		height_ = size;
		width_ = size * 4.f;
		isCrashed_ = false;

		// Set shape's options
		rectangle_.setSize(sf::Vector2f(width_, height_));
		rectangle_.setFillColor(getRandomColor());
		rectangle_.setOutlineThickness(1);
		rectangle_.setOutlineColor(sf::Color::Black);

		position_ = position;
		SetRelativeOrigin(rectangle_, 0.5f, 0.5f);
		rectangle_.setPosition(position_.x, position_.y);
	}

	void Block::update(const float& deltaTime) {}

	void Block::draw() {
		window_.draw(rectangle_);
	}

	// Check is ball collide with block and if it is, returns index, which coordinate axis must change
	int Block::checkCollide(std::shared_ptr<GameObject> object) {

		float xNormal = object->getHeight() + 1.f;
		float yNormal = object->getHeight() + 1.f;

		// Search area of triangle between ball's origin and block's side
		auto triangleArea = [](float x1, float y1, float x2, float y2, float x3, float y3) {
			return std::fabs((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1)) / 2.f;
		};

		// Search length of block's side
		auto baseLength = [](float x1, float y1, float x2, float y2) {
			return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
		};

		// Search normal from ball's orifin to block's side
		auto triangleHeight = [](float triangleArea, float baseLenght) {
			return triangleArea * 2.f / baseLenght;
		};
		
		if ((object->getOriginX() > getOriginX() - getWidth() / 2.f) &&
			(object->getOriginX() < getOriginX() + getWidth() / 2.f)) {

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
		else if ((object->getOriginY() > getOriginY() - getHeight() / 2.f) &&
				 (object->getOriginY() < getOriginY() + getHeight() / 2.f)) {

			float area1 = triangleArea(object->getOriginX(), object->getOriginY(),
				getOriginX() - getWidth() / 2.f, getOriginY() - getHeight() / 2.f,
				getOriginX() - getWidth() / 2.f, getOriginY() + getHeight() / 2.f);

			float area2 = triangleArea(object->getOriginX(), object->getOriginY(),
				getOriginX() + getWidth() / 2.f, getOriginY() - getHeight() / 2.f,
				getOriginX() + getWidth() / 2.f, getOriginY() + getHeight() / 2.f);

			float length = baseLength(getOriginX() - getWidth() / 2.f, getOriginY() - getHeight() / 2.f,
				getOriginX() - getWidth() / 2.f, getOriginY() + getHeight() / 2.f);

			xNormal = area1 < area2 ? triangleHeight(area1, length) : triangleHeight(area2, length);
		}

		if (yNormal <= object->getWidth() / 2.f) {
			isCrashed_ = true;
			return 1;
		}
		else if (xNormal <= object->getWidth() / 2.f) {
			isCrashed_ = true;
			return 2;
		}

		return 0;
	}

	float Block::getOriginX() const {
		return position_.x;
	}
	
	float Block::getOriginY() const {
		return position_.y;
	}

	float Block::getWidth() const {
		return width_;
	}

	float Block::getHeight() const {
		return height_;
	}
}