#pragma once

#include "Resources.h"
#include "Engine.h"

namespace ArkanoidGame {

	enum class PlatformDirection : int {
		None = 0,
		Right,
		Left,
	};

	class Platform {
	public:
		Platform(Resources& resources, sf::RenderWindow& window);

		void init(int width, float speed);
		void move(const float& deltaTime);
		void draw();

	private:
		int width_ = 0;
		const int height_ = 20;
		float speed_ = 0.f;

		sf::Vector2f position_;

		sf::RectangleShape rectangle_;

		PlatformDirection direction_ = PlatformDirection::None;

		sf::Keyboard::Key leftKey_ = sf::Keyboard::Left;
		sf::Keyboard::Key rightKey_ = sf::Keyboard::Right;

		Resources& resources_;
		sf::RenderWindow& window_;
	};
}

