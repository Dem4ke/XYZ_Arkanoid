#pragma once

#include "Player.h"

namespace SnakeGame {

	class Wall {
	public:
		Wall(Resources& resources) : resources_(resources) {}

		void init();

		float getSize() const;
		sf::Sprite getSprite() const;


	private:

		sf::Sprite sprite_;
		Resources& resources_;
	};
}
