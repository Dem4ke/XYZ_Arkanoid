#pragma once

#include <SFML/Graphics.hpp>
#include "../IGameObject.h"
#include "../Observer/Subject.h"

namespace Arkanoid
{
	class UBonus : public IGameObject, public IBonusSubject
	{
	public:
		UBonus(const sf::Vector2f& InputedPosition);
		UBonus(const UBonus& Bonus);
		virtual ~UBonus() = default;

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

		std::shared_ptr<IGameObject> clone() const override;

		void Attach(std::shared_ptr<IBonusObserver> Observer) override;
		void Detach(std::shared_ptr<IBonusObserver> Observer) override;
		void Notify(bool bIsTaken) override;

	protected:
		int BonusType = 0;			// Type of taken bonus
		bool bIsDestroyed = false;	// Flag shows that bonus destroyed

		float Size = 30.f;			// Size of the bonus
		float Speed = 100.f;		// Speed of the bonus
		float Angle = 90.f;			// Angle of bonus's velocity

		EObjectType Type = EObjectType::Bonus;	// Type of current game object

		sf::Vector2f Position;		// Position of the bonus on screen
		sf::Vector2f Direction;		// Unit vector that contains bonus's velocity direction
		sf::CircleShape Circle;		// Shape of the bonus

		std::vector<std::shared_ptr<IBonusObserver>> Observers;// Vector of observers
	};

	class UFireBallBonus : public UBonus
	{
	public:
		UFireBallBonus(const sf::Vector2f& InputedPosition);
		UFireBallBonus(const UFireBallBonus& Bonus);
		~UFireBallBonus() = default;

	private:
		int BonusType = 1;
	};

	class UGlassBlocksBonus : public UBonus
	{
	public:
		UGlassBlocksBonus(const sf::Vector2f& InputedPosition);
		UGlassBlocksBonus(const UGlassBlocksBonus& Bonus);
		~UGlassBlocksBonus() = default;

	private:
		int BonusType = 2;
	};

	class UBigPlatformBonus : public UBonus
	{
	public:
		UBigPlatformBonus(const sf::Vector2f& InputedPosition);
		UBigPlatformBonus(const UBigPlatformBonus& Bonus);
		~UBigPlatformBonus() = default;

	private:
		int BonusType = 3;
	};
}