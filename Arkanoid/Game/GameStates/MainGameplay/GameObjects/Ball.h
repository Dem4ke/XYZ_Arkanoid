#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../IGameObject.h"

namespace Arkanoid
{
	class UBall final : public IGameObject
	{
	public:
		UBall(const sf::Vector2f& InputedPosition);
		~UBall() = default;

		void Update(const float& DeltaTime) override;
		void Draw(sf::RenderWindow& Window) override;

		void CheckCollision(std::shared_ptr<IGameObject> Object) override;

		float GetOriginX() const override;
		float GetOriginY() const override;
		float GetWidth() const override;
		float GetHeight() const override;

	private:
		void ChangeX();
		void ChangeY();

		float Size = 10.f;			// Size of the ball
		float Speed = 60.f;			// Speed of the ball
		float Angle = 0.f;			// Angle of ball's velocity

		bool bIsOutOfPlayground = false;

		sf::Vector2f Position;		// Position of the ball on screen
		sf::Vector2f Direction;		// Unit vector that contains ball's velocity direction

		sf::CircleShape Circle;		// Shape of the ball

		sf::SoundBuffer HitSound;	// Sound of menu moves
	};
}