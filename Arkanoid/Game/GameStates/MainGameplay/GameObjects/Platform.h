#pragma once

#include <SFML/Graphics.hpp>
#include "../IGameObject.h"
#include "../../CButton.h"

namespace Arkanoid
{
	class UPlatform final : public IGameObject
	{
	public:
		UPlatform(const sf::Vector2f& InputedPosition);
		~UPlatform() = default;

		void Update(const float& DeltaTime) override;
		void Draw(sf::RenderWindow& Window) override;

		void CheckCollision(std::shared_ptr<IGameObject> Object) override;

		float GetOriginX() const override;
		float GetOriginY() const override;
		float GetWidth() const override;
		float GetHeight() const override;

	private:
		float Width = 240.f;			// Width of the platform
		float Height = 40.f;			// Height of the platform
		float Speed = 40.f;				// Speed of the platform

		sf::Vector2f Position;			// Position of the platform on screen
		sf::Texture Texture;			// Texture of the platform
		sf::Sprite Sprite;				// Sprite to draw

		CButton Button;					// Keys to work with the game
	};
}