#include <cassert>
#include "Ball.h"
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

		Circle.setRadius(Size / 2.f);
		Circle.setFillColor(sf::Color::White);
		Math::SetRelativeOrigin(Circle, 0.5f, 0.5f);

		// Set started direction of ball (unit vector)
		const float pi = std::acos(-1.f);
		Direction.x = std::cos(pi / 180.f * Angle);
		Direction.y = std::sin(pi / 180.f * Angle);

		// Set start position
		Circle.setPosition(Position);
	}

	void UBall::Update(const float& DeltaTime) 
	{
		// Calculate new position of ball
		Position += (Speed * DeltaTime * Direction);
		Circle.setPosition(Position);

		// Check collision with window's borders
		if (Position.x - Size / 2.f < 0 || Position.x + Size / 2.f > SETTINGS.GetScreenWidth()) {
			ChangeX();
		}

		if (Position.y - Size / 2.f < 0) {
			ChangeY();
		}

		if (Position.y + Size / 2.f > SETTINGS.GetScreenHeight()) {
			bIsOutOfPlayground = true;
		}
	}

	void UBall::Draw(sf::RenderWindow& Window)
	{
		Window.draw(Circle);
	}

	void UBall::CheckCollision(std::shared_ptr<IGameObject> Object)
	{
		// Light check is lenght between ball and block is more than width of block + size of ball  
		double Length = sqrt((Object->GetOriginX() - GetOriginX()) * (Object->GetOriginX() - GetOriginX()) +
							 (Object->GetOriginY() - GetOriginY()) * (Object->GetOriginY() - GetOriginY()));

		if (Length < Object->GetWidth() + GetWidth())
		{
			float NormalX = Object->GetWidth() * 2.f;
			float NormalY = Object->GetWidth() * 2.f;

			// Search area of triangle between ball's origin and block's side
			auto TriangleArea = [](float x1, float y1, float x2, float y2, float x3, float y3)
				{
					return std::fabs((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1)) / 2.f;
				};

			// Search length of block's side
			auto BaseLength = [](float x1, float y1, float x2, float y2)
				{
					return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
				};

			// Search lenght of the normal from ball's orifin to block's side
			auto TriangleHeight = [](float triangleArea, float baseLenght)
				{
					return triangleArea * 2.f / baseLenght;
				};

			// Check lenght of the normal from ball to block
			if ((GetOriginX() + (GetWidth() / 2.f) * 0.85f > Object->GetOriginX() - Object->GetWidth() / 2.f) &&
				(GetOriginX() - (GetWidth() / 2.f) * 0.85f < Object->GetOriginX() + Object->GetWidth() / 2.f))
			{
				float Area1 = TriangleArea(GetOriginX(), GetOriginY(),
					Object->GetOriginX() - Object->GetWidth() / 2.f, Object->GetOriginY() + Object->GetHeight() / 2.f,
					Object->GetOriginX() + Object->GetWidth() / 2.f, Object->GetOriginY() + Object->GetHeight() / 2.f);

				float Area2 = TriangleArea(GetOriginX(), GetOriginY(),
					Object->GetOriginX() - Object->GetWidth() / 2.f, Object->GetOriginY() - Object->GetHeight() / 2.f,
					Object->GetOriginX() + Object->GetWidth() / 2.f, Object->GetOriginY() - Object->GetHeight() / 2.f);

				float Length = BaseLength(Object->GetOriginX() - Object->GetWidth() / 2.f, Object->GetOriginY() + Object->GetHeight() / 2.f,
										  Object->GetOriginX() + Object->GetWidth() / 2.f, Object->GetOriginY() + Object->GetHeight() / 2.f);

				NormalY = Area2 < Area2 ? TriangleHeight(Area1, Length) : TriangleHeight(Area2, Length);
			}
			else if ((Object->GetOriginY() + (Object->GetHeight() / 2.f) * 0.85f > GetOriginY() - GetHeight() / 2.f) &&
				(Object->GetOriginY() - (Object->GetHeight() / 2.f) * 0.85f < GetOriginY() + GetHeight() / 2.f))
			{
				float Area1 = TriangleArea(GetOriginX(), GetOriginY(),
					Object->GetOriginX() - Object->GetWidth() / 2.f, Object->GetOriginY() - Object->GetHeight() / 2.f,
					Object->GetOriginX() - Object->GetWidth() / 2.f, Object->GetOriginY() + Object->GetHeight() / 2.f);

				float Area2 = TriangleArea(GetOriginX(), GetOriginY(),
					Object->GetOriginX() + Object->GetWidth() / 2.f, Object->GetOriginY() - Object->GetHeight() / 2.f,
					Object->GetOriginX() + Object->GetWidth() / 2.f, Object->GetOriginY() + Object->GetHeight() / 2.f);

				float Length = BaseLength(Object->GetOriginX() - Object->GetWidth() / 2.f, Object->GetOriginY() - Object->GetHeight() / 2.f,
										  Object->GetOriginX() - Object->GetWidth() / 2.f, Object->GetOriginY() + Object->GetHeight() / 2.f);

				NormalX = Area1 < Area2 ? TriangleHeight(Area1, Length) : TriangleHeight(Area2, Length);
			}

			// Change ball's velocity 
			if (NormalY < GetHeight() / 2.f)
			{
				ChangeY();
			}
			else if (NormalX < GetWidth() / 2.f)
			{
				ChangeX();
			}
		}
	}

	float UBall::GetOriginX() const
	{
		return Circle.getOrigin().x;
	}

	float UBall::GetOriginY() const
	{
		return Circle.getOrigin().y;
	}

	float UBall::GetWidth() const
	{
		return Size;
	}

	float UBall::GetHeight() const
	{
		return Size;
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
}