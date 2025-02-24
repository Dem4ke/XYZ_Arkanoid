#pragma once

#include <SFML/Graphics.hpp>
#include "../IGameObject.h"

namespace Arkanoid
{
	class UPlatform final : public IGameObject
	{
	public:
		UPlatform(const sf::Vector2f& InputedPosition);

	private:
		float Width = 125.f;							// Width of block
		float Height = 40.f;							// Height of block

		sf::Vector2f Position;							// Position of the block on screen
		sf::Texture Texture;							// Texture of the block
		sf::Sprite Sprite;								// Sprite to draw
	};
}