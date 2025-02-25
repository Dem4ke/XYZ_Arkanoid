#pragma once

#include <SFML/Graphics.hpp>
#include "../IGameObject.h"

namespace Arkanoid
{
	class UBall final : public IGameObject
	{
	public:
		UBall(const sf::Vector2f& InputedPosition);
		~UBall() = default;

		void Update(const float& deltaTime) override;
		void Draw(sf::RenderWindow& Window) override;

		void CheckCollision(std::shared_ptr<IGameObject> Object) override;

		float GetOriginX() const override;
		float GetOriginY() const override;
		float GetWidth() const override;
		float GetHeight() const override;

	private:
		float Size = 10.f;			// Size of the ball
		float Speed = 60.f;			// Speed of the ball

		sf::Vector2f Position;		// Position of the ball on screen
		sf::Texture Texture;		// Texture of the ball
		sf::Sprite Sprite;			// Sprite to draw
	};
}