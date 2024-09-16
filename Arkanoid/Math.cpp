#include "Math.h"

namespace ArkanoidGame {
	bool IsCircleAndRectangleCollide(float radius, float circusCenterX, float circusBottomY, 
									 float rectTopLeftX, float rectTopRightX, float rectTopY) {
		if (circusBottomY >= rectTopY) {
			if ((circusCenterX + radius) >= rectTopLeftX &&
				(circusCenterX - radius) <= rectTopRightX) {

				return true;
			}
		}

		return false;
	}

	sf::Color getRandomColor() {
		int index = rand() / (float)RAND_MAX * 6;

		switch (index) {
		case 0: {
			return sf::Color::Blue;			
		}
		case 1: {
			return sf::Color::Red;
		}
		case 2: {
			return sf::Color::Green;
		}
		case 3: {
			return sf::Color::Cyan;
		}
		case 4: {
			return sf::Color::White;
		}
		case 5: {
			return sf::Color::Yellow;
		}
		case 6: {
			return sf::Color::Magenta;
		}
		} 
	}

	void SetSize(sf::Sprite& sprite, float desiredWidht, float desiredHeight) {
		// Get sprite size from the corner
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidht / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}
}
