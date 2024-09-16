#pragma once

#include <SFML/Graphics.hpp>

namespace ArkanoidGame {

	class GameObject {
	public:
		virtual ~GameObject() = default;

		virtual void init(float size, float speed, sf::Vector2f position) = 0;
		virtual void update(const float& deltaTime) = 0;
		virtual void draw() = 0;

		virtual float getOriginX() const = 0;
		virtual float getOriginY() const = 0;
		virtual float getWidth() const = 0;
		virtual float getHeight() const = 0;
	};
}