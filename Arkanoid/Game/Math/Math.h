#pragma once
#include <SFML/Graphics.hpp>

namespace Math 
{
	sf::Color GetRandomColor();

	// Sprites and rectangles
	void SetSize(sf::Sprite& Sprite, float DesiredWidht, float DesiredHeight);

	template <typename T>
	void SetRelativeOrigin(T& Sprite, float OriginX, float OriginY)
	{
		sf::FloatRect SpriteRect = Sprite.getLocalBounds();
		Sprite.setOrigin(sf::Vector2f(OriginX * SpriteRect.width, OriginY * SpriteRect.height));
	}
}