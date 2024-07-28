#include "Apple.h"

namespace SnakeGame {

	Apple::Apple() {}

	void Apple::init(int cost) {
		cost_ = cost;
		isExists_ = false;
	}

	void Apple::setStatus(bool isExists) {
		isExists_ = isExists;
	}

	void Apple::setPositionOnField(int position) {
		positionOnField_ = position;
	}

	int Apple::getPositionOnField() const {	return positionOnField_; }

	int Apple::getCost() const { return cost_; }

	bool Apple::isAppleExists() const {	return isExists_; }

}