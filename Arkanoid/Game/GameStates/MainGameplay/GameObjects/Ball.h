#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../IGameObject.h"
#include "../Observer/Subject.h"

namespace Arkanoid
{
	class UBall final : public IGameObject, public IBallSubject
	{
	public:
		UBall(const sf::Vector2f& InputedPosition);
		~UBall() = default;

		void Update(const float& DeltaTime) override;
		void Draw(sf::RenderWindow& Window) override;
		bool CheckCollision(std::shared_ptr<IGameObject> Object, EObjectType Type) override;
		void Hit() override;

		float GetOriginX() const override;
		float GetOriginY() const override;
		float GetWidth() const override;
		float GetHeight() const override;

		EObjectType GetObjectType() const override;
		bool IsDestroyed() const override;

		void Attach(std::shared_ptr<IBallObserver> Observer) override;
		void Detach(std::shared_ptr<IBallObserver> Observer) override;
		void Notify() override;

	private:
		void ChangeX();
		void ChangeY();
		void ChangeAngle(float NewAngle);

		float Size = 30.f;			// Size of the ball
		float Speed = 240.f;		// Speed of the ball
		float Angle = -90.f;		// Angle of ball's velocity

		EObjectType Type = EObjectType::Ball;	// Type of current game object

		sf::Vector2f Position;		// Position of the ball on screen
		sf::Vector2f Direction;		// Unit vector that contains ball's velocity direction
		sf::CircleShape Circle;		// Shape of the ball
		sf::SoundBuffer HitSound;	// Sound of menu moves

		std::vector<std::shared_ptr<IBallObserver>> Observers;// Vector of observers
	};
}