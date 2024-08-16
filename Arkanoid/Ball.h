#pragma once

#include "Resources.h"
#include "Engine.h"

namespace ArkanoidGame {

	class Ball {
	public:
		Ball(Resources& resources, sf::RenderWindow& window);

		void init(float size = 20.f, float speed = 1000.f);
		void move(const float& deltaTime);
		void draw();

	private:
		float size_ = 0;
		float speed_ = 0;

		sf::Vector2f position_;
		sf::Vector2f direction_;

		sf::RectangleShape rectangle_;
		sf::CircleShape circle_;

		Resources& resources_;
		sf::RenderWindow& window_;
	};
}
