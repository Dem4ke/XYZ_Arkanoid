#include "Block.h"

namespace ArkanoidGame {
	Block::Block(Resources& resources, sf::RenderWindow& window) :
		resources_(resources), window_(window) {}

	void Block::init(float size, float speed) {}

	void Block::update(const float& deltaTime) {}

	void Block::draw() {}
}