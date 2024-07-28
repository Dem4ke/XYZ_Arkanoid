#include "Player.h"

namespace SnakeGame {

	// PLAYER INITIALIZATION

	Player::Player() {}

	void Player::init(float speed, int size, int position) {
		// Initialization of player's characteristics
		direction_ = PlayerDirection::Right;
		speed_ = speed * 1000;
		size_ = size;

		// Set head position
		positionOnField_.clear();
		positionOnField_.push_back(position); 

		// Set body position
		for (int i = 1; i < size_; ++i) {
			positionOnField_.push_back(position - i);
		}
	}

	void Player::moveRight() {
		direction_ = PlayerDirection::Right;
	}

	void Player::moveLeft() {
		direction_ = PlayerDirection::Left;
	}

	void Player::moveUp() {
		direction_ = PlayerDirection::Up;
	}

	void Player::moveDown() {
		direction_ = PlayerDirection::Down;
	}

	void Player::sizeIncrease() {
		++size_;
		positionOnField_.push_back(positionBuffer_);
	}

	void Player::setPositionOnField(int newPosition) {
		// Get position of last body element to buffer
		positionBuffer_ = positionOnField_[positionOnField_.size() - 1];

		// Set body position
		for (int i = size_ - 1; i > 0; --i) {
			positionOnField_[i] = positionOnField_[i - 1];
		}

		// Set head position
		positionOnField_[0] = newPosition;
	}

	int Player::getPositionOnField(int index) const { return positionOnField_[index]; }

	int Player::getSize() const { return size_; }

	int Player::getSpeed() const { return speed_; }

	PlayerDirection Player::getDirection() const { return direction_; }
}