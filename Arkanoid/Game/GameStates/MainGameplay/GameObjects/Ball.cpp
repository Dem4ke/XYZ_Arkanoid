#include <cassert>
#include "Ball.h"
#include "../Observer/Observer.h"
#include "../../../Math/Math.h"
#include "../../../Settings/Settings.h"

namespace Arkanoid
{
	UBall::UBall(const sf::Vector2f& InputedPosition)
		: Position(InputedPosition)
	{
		// Load sound of ball's hit
		bool bIsLoaded = HitSound.loadFromFile("Resources/Sounds/Owlstorm__Snake_hit.wav");
		assert(bIsLoaded);

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

	UBall::UBall(const UBall& Ball)
		: Size(Ball.Size)
		, Speed(Ball.Speed)
		, Angle(Ball.Angle)
		, Type(Ball.Type)
		, Position(Ball.Position)
		, Direction(Ball.Direction)
		, Circle(Ball.Circle)
		, HitSound(Ball.HitSound)
		, Observers(Ball.Observers)
	{}

	void UBall::Update(const float& DeltaTime) 
	{
		// Calculate new position of ball
		Position += (Speed * DeltaTime * Direction);
		Circle.setPosition(Position);

		// Check collision with window's borders
		if (Position.x - Size / 2.f < 0 || Position.x + Size / 2.f > SETTINGS.GetScreenWidth()) 
		{
			ChangeX();
		}

		if (Position.y - Size / 2.f < 0) 
		{
			ChangeY();
		}

		if (Position.y + Size / 2.f > SETTINGS.GetScreenHeight()) 
		{
			// Notify observers that ball is out of screen
			Notify();
		}
	}

	void UBall::Draw(sf::RenderWindow& Window)
	{
		Window.draw(Circle);
	}

	bool UBall::CheckCollision(std::shared_ptr<IGameObject> Object, EObjectType Type)
	{
		// Light check is lenght between ball and object is more than width of object + size of ball  
		float Length = sqrt(((Object->GetOriginX() - GetOriginX()) * (Object->GetOriginX() - GetOriginX())) +
							((Object->GetOriginY() - GetOriginY()) * (Object->GetOriginY() - GetOriginY())));

		if (Length < (Object->GetWidth() + GetWidth()))
		{
			float NormalX = GetWidth() * 2.f;
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
			else if ((GetOriginY() + (GetHeight() / 2.2f) >= Object->GetOriginY() - Object->GetHeight() / 2.f) &&
					 (GetOriginY() - (GetHeight() / 2.2f) <= Object->GetOriginY() + Object->GetHeight() / 2.f))
			{
				float Area1 = TriangleArea(GetOriginX(), GetOriginY(),
					Object->GetOriginX() - Object->GetWidth() / 2.f, Object->GetOriginY() - Object->GetHeight() / 2.f,
					Object->GetOriginX() - Object->GetWidth() / 2.f, Object->GetOriginY() + Object->GetHeight() / 2.f);

				float Area2 = TriangleArea(GetOriginX(), GetOriginY(),
					Object->GetOriginX() + Object->GetWidth() / 2.f, Object->GetOriginY() - Object->GetHeight() / 2.f,
					Object->GetOriginX() + Object->GetWidth() / 2.f, Object->GetOriginY() + Object->GetHeight() / 2.f);

				NormalX = Area1 < Area2 ? TriangleHeight(Area1, Object->GetHeight()) : TriangleHeight(Area2, Object->GetHeight());
			}

			// Change ball's velocity 
			if (NormalY <= GetHeight() / 2.f && NormalY >= 1.f)
			{
				switch (Type)
				{
				case EObjectType::Platform:
				{
					// Find relative place of collide (-1 is left corner, 1 is right corner)
					float CollidePlace = (GetOriginX() - Object->GetOriginX()) / Object->GetWidth() / 2.f;

					float NewAngle = 90.f - 120.f * CollidePlace;
					ChangeAngle(NewAngle);
					break;
				}
				default:
				{
					Object->Hit();
					ChangeY();
					break;
				}
				}
				return true;
			}
			else if (NormalX <= GetWidth() / 2.f && NormalX >= 1.f)
			{
				Object->Hit();
				ChangeX();
				return true;
			}
		}

		return false;
	}

	void UBall::Hit() {}

	float UBall::GetOriginX() const
	{
		return Position.x;
	}

	float UBall::GetOriginY() const
	{
		return Position.y;
	}

	float UBall::GetWidth() const
	{
		return Size;
	}

	float UBall::GetHeight() const
	{
		return Size;
	}

	EObjectType UBall::GetObjectType() const
	{
		return Type;
	}

	bool UBall::IsDestroyed() const
	{
		return false;
	}

	std::shared_ptr<IGameObject> UBall::clone() const
	{
		return std::make_shared<UBall>(*this);
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	       SUBJECT METHODS          */
	/*                                  */
	/*//////////////////////////////////*/

	void UBall::Attach(std::shared_ptr<IBallObserver> Observer)
	{
		Observers.push_back(Observer);
	}

	void UBall::Detach(std::shared_ptr<IBallObserver> Observer)
	{
		Observers.erase(std::remove(Observers.begin(), Observers.end(), Observer), Observers.end());
	}

	void UBall::Notify()
	{
		for (auto& i : Observers)
		{
			i->BallOut();
		}
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	      PRIVATE WORKTOOLS         */
	/*                                  */
	/*//////////////////////////////////*/

	void UBall::ChangeX()
	{
		Direction.x *= -1;
		SETTINGS.GetResources()->PlaySound(HitSound);
	}

	void UBall::ChangeY()
	{
		Direction.y *= -1;
		SETTINGS.GetResources()->PlaySound(HitSound);
	}

	// Set new angle to the ball
	void UBall::ChangeAngle(float NewAngle)
	{
		const auto pi = std::acos(-1.f);
		Direction.x = (NewAngle / abs(NewAngle)) * std::cos(pi / 180.f * NewAngle);;
		Direction.y = -1 * abs(std::sin(pi / 180.f * NewAngle));

		SETTINGS.GetResources()->PlaySound(HitSound);
	}
}