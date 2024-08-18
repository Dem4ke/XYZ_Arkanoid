#pragma once

#include <SFML/Graphics.hpp>

namespace ArkanoidGame {

	bool IsCircleAndRectangleCollide(float radius, float circusCenterX, float circusBottomY, float rectTopLeftX, float rectTopRightX, float rectTopY);

	// Sprites and rectangles
	template <typename T>
	void SetSize(T& sprite, float desiredWidht, float desiredHeight) {
		// Get sprite size from the corner
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidht / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}

	template <typename T>
	void SetRelativeOrigin(T& sprite, float originX, float originY) {
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(sf::Vector2f(originX * spriteRect.width, originY * spriteRect.height));
	}
}