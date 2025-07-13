#include <cassert>
#include "Bonus.h"
#include "../Observer/Observer.h"
#include "../../../Math/Math.h"
#include "../../../Settings/Settings.h"

namespace Arkanoid
{
	UBonus::UBonus(const sf::Vector2f& InputedPosition)
		: Position(InputedPosition)
	{
		Size *= SETTINGS.GetScaleFactor().X;
		Speed *= SETTINGS.GetScaleFactor().X;

		Circle.setRadius(Size / 2.f);
		Circle.setFillColor(sf::Color::White);
		Math::SetRelativeOrigin(Circle, 0.5f, 0.5f);

		// Set started direction of ball (unit vector)
		const float pi = std::acos(-1.f);
		Direction.x = std::cos(pi / 180.f * Angle);
		Direction.y = std::sin(pi / 180.f * Angle);

		// Set start position
		Position.y -= Size / 2.f;
		Circle.setPosition(Position);
	}

	UBonus::UBonus(const UBonus& Bonus)
		: Size(Bonus.Size)
		, Speed(Bonus.Speed)
		, Angle(Bonus.Angle)
		, Type(Bonus.Type)
		, Position(Bonus.Position)
		, Direction(Bonus.Direction)
		, Circle(Bonus.Circle)
		, Observers(Bonus.Observers)
	{
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	     GAME OBJECT METHODS        */
	/*                                  */
	/*//////////////////////////////////*/

	void UBonus::Update(const float& DeltaTime) 
	{
		// Calculate new position of bonus
		Position += (Speed * DeltaTime * Direction);
		Circle.setPosition(Position);

		if (Position.y + Size / 2.f > SETTINGS.GetScreenHeight()) 
		{
			// Notify observers that bonus need to be deleted
			Notify(false);
		}
	}

	void UBonus::Draw(sf::RenderWindow& Window)
	{
		Window.draw(Circle);
	}

	bool UBonus::CheckCollision(std::shared_ptr<IGameObject> Object, EObjectType Type)
	{
		// Light check is lenght between ball and object is more than width of object + size of ball  
		float Length = sqrt(((Object->GetOriginX() - GetOriginX()) * (Object->GetOriginX() - GetOriginX())) +
			((Object->GetOriginY() - GetOriginY()) * (Object->GetOriginY() - GetOriginY())));

		if (Length < (Object->GetWidth() + GetWidth()))
		{
			float NormalY = GetWidth() * 2.f;

			// Search area of triangle between ball's origin and object's side
			auto TriangleArea = [](float x1, float y1, float x2, float y2, float x3, float y3)
				{
					return std::fabs((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1)) / 2.f;
				};

			// Search lenght of the normal from ball's origin to object's side
			auto TriangleHeight = [](float triangleArea, float baseLenght)
				{
					return triangleArea * 2.f / baseLenght;
				};

			// Check lenght of the normal from ball to object
			if ((GetOriginX() + (GetWidth() / 2.2f) >= Object->GetOriginX() - Object->GetWidth() / 2.f) &&
				(GetOriginX() - (GetWidth() / 2.2f) <= Object->GetOriginX() + Object->GetWidth() / 2.f))
			{
				float Area1 = TriangleArea(GetOriginX(), GetOriginY(),
					Object->GetOriginX() - Object->GetWidth() / 2.f, Object->GetOriginY() + Object->GetHeight() / 2.f,
					Object->GetOriginX() + Object->GetWidth() / 2.f, Object->GetOriginY() + Object->GetHeight() / 2.f);

				float Area2 = TriangleArea(GetOriginX(), GetOriginY(),
					Object->GetOriginX() - Object->GetWidth() / 2.f, Object->GetOriginY() - Object->GetHeight() / 2.f,
					Object->GetOriginX() + Object->GetWidth() / 2.f, Object->GetOriginY() - Object->GetHeight() / 2.f);

				NormalY = Area1 < Area2 ? TriangleHeight(Area1, Object->GetWidth()) : TriangleHeight(Area2, Object->GetWidth());
			}

			// Notify that bonus has been taken
			if (NormalY <= GetHeight() / 2.f && NormalY >= 1.f)
			{
				Notify(true);
				return true;
			}
		}

		return false;
	}

	void UBonus::Hit() {}

	float UBonus::GetOriginX() const
	{
		return Position.x;
	}

	float UBonus::GetOriginY() const
	{
		return Position.y;
	}

	float UBonus::GetWidth() const
	{
		return Size;
	}

	float UBonus::GetHeight() const
	{
		return Size;
	}

	EObjectType UBonus::GetObjectType() const
	{
		return Type;
	}

	bool UBonus::IsDestroyed() const
	{
		return bIsDestroyed;
	}

	std::shared_ptr<IGameObject> UBonus::clone() const
	{
		return std::make_shared<UBonus>(*this);
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	       SUBJECT METHODS          */
	/*                                  */
	/*//////////////////////////////////*/

	void UBonus::Attach(std::shared_ptr<IBonusObserver> Observer)
	{
		Observers.push_back(Observer);
	}

	void UBonus::Detach(std::shared_ptr<IBonusObserver> Observer)
	{
		Observers.erase(std::remove(Observers.begin(), Observers.end(), Observer), Observers.end());
	}

	void UBonus::Notify(bool bIsTaken)
	{
		if (bIsTaken)
		{
			for (auto& i : Observers)
			{
				i->BonusTaken(BonusType);
			}
		}
		else
		{
			for (auto& i : Observers)
			{
				i->BonusTaken(0);
			}
		}

		bIsDestroyed = true;
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	       FIRE BALL BONUS          */
	/*                                  */
	/*//////////////////////////////////*/
	
	UFireBallBonus::UFireBallBonus(const sf::Vector2f& InputedPosition)
		: UBonus(InputedPosition)
	{
		Circle.setFillColor(sf::Color::Red);
	}

	UFireBallBonus::UFireBallBonus(const UFireBallBonus& Bonus)
		: UBonus(Bonus)
	{
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	      GLASS BLOCKS BONUS        */
	/*                                  */
	/*//////////////////////////////////*/

	UGlassBlocksBonus::UGlassBlocksBonus(const sf::Vector2f& InputedPosition)
		: UBonus(InputedPosition)
	{
		Circle.setFillColor(sf::Color::Green);
	}

	UGlassBlocksBonus::UGlassBlocksBonus(const UGlassBlocksBonus& Bonus)
		: UBonus(Bonus)
	{
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	      BIG PLATFORM BONUS        */
	/*                                  */
	/*//////////////////////////////////*/

	UBigPlatformBonus::UBigPlatformBonus(const sf::Vector2f& InputedPosition)
		: UBonus(InputedPosition)
	{
		Circle.setFillColor(sf::Color::Yellow);
	}

	UBigPlatformBonus::UBigPlatformBonus(const UBigPlatformBonus& Bonus)
		: UBonus(Bonus)
	{
	}

}