#pragma once

#include <SFML/Graphics.hpp>

namespace ArkanoidGame {

	sf::Color GetRandomColor();

	// Sprites and rectangles
	void SetSize(sf::Sprite& sprite, float desiredWidht, float desiredHeight);

	template <typename T>
	void SetRelativeOrigin(T& sprite, float originX, float originY) {
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(sf::Vector2f(originX * spriteRect.width, originY * spriteRect.height));
	}
}