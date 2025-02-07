#include "Math.h"

namespace Math 
{
	sf::Color GetRandomColor() 
	{
		int Index = static_cast<int> (rand() / (float)RAND_MAX * 6);

		switch (Index) 
		{
		case 0: 
		{
			return sf::Color::Blue;
		}
		case 1: 
		{
			return sf::Color::Red;
		}
		case 2: 
		{
			return sf::Color::Green;
		}
		case 3: 
		{
			return sf::Color::Cyan;
		}
		case 4: 
		{
			return sf::Color::White;
		}
		case 5: 
		{
			return sf::Color::Yellow;
		}
		case 6: 
		{
			return sf::Color::Magenta;
		}
		}
	}

	void SetSize(sf::Sprite& Sprite, float DesiredWidht, float DesiredHeight)
	{
		// Get sprite size from the corner
		sf::FloatRect SpriteRect = Sprite.getLocalBounds();
		sf::Vector2f Scale = { DesiredWidht / SpriteRect.width, DesiredHeight / SpriteRect.height };
		Sprite.setScale(Scale);
	}
}