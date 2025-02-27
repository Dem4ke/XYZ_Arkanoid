#include "Ball.h"
#include "../../../Math/Math.h"

namespace Arkanoid
{
	UBall::UBall(const sf::Vector2f& InputedPosition)
	: Position(InputedPosition)
	{

	}

	void UBall::Update(const float& deltaTime) 
	{

	}

	void UBall::Draw(sf::RenderWindow& Window)
	{
		Window.draw(Sprite);
	}

	void UBall::CheckCollision(std::shared_ptr<IGameObject> Object)
	{
		// Light check is lenght between ball and block is more than width of block + size of ball  
		double Length = sqrt((Object->GetOriginX() - GetOriginX()) * (Object->GetOriginX() - GetOriginX()) +
							 (Object->GetOriginY() - GetOriginY()) * (Object->GetOriginY() - GetOriginY()));

		if (Length < Object->GetWidth() + GetWidth())
		{
			float xNormal = Object->GetWidth() * 2.f;
			float yNormal = Object->GetWidth() * 2.f;

			// Search area of triangle between ball's origin and block's side
			auto triangleArea = [](float x1, float y1, float x2, float y2, float x3, float y3)
				{
					return std::fabs((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1)) / 2.f;
				};

			// Search length of block's side
			auto baseLength = [](float x1, float y1, float x2, float y2)
				{
					return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
				};

			// Search normal from ball's orifin to block's side
			auto triangleHeight = [](float triangleArea, float baseLenght)
				{
					return triangleArea * 2.f / baseLenght;
				};


			// Check normal lenght from ball to block
			if ((Object->GetOriginX() + (Object->GetWidth() / 2.f) * 0.85f > GetOriginX() - GetWidth() / 2.f) &&
				(Object->GetOriginX() - (Object->GetWidth() / 2.f) * 0.85f < GetOriginX() + GetWidth() / 2.f))
			{
				float area1 = triangleArea(Object->GetOriginX(), Object->GetOriginY(),
					GetOriginX() - GetWidth() / 2.f, GetOriginY() + GetHeight() / 2.f,
					GetOriginX() + GetWidth() / 2.f, GetOriginY() + GetHeight() / 2.f);

				float area2 = triangleArea(Object->GetOriginX(), Object->GetOriginY(),
					GetOriginX() - GetWidth() / 2.f, GetOriginY() - GetHeight() / 2.f,
					GetOriginX() + GetWidth() / 2.f, GetOriginY() - GetHeight() / 2.f);

				float length = baseLength(GetOriginX() - GetWidth() / 2.f, GetOriginY() + GetHeight() / 2.f,
					GetOriginX() + GetWidth() / 2.f, GetOriginY() + GetHeight() / 2.f);

				yNormal = area1 < area2 ? triangleHeight(area1, length) : triangleHeight(area2, length);
			}
			else if ((Object->GetOriginY() + (Object->GetHeight() / 2.f) * 0.85f > GetOriginY() - GetHeight() / 2.f) &&
				(Object->GetOriginY() - (Object->GetHeight() / 2.f) * 0.85f < GetOriginY() + GetHeight() / 2.f))
			{
				float area1 = triangleArea(Object->GetOriginX(), Object->GetOriginY(),
					GetOriginX() - GetWidth() / 2.f, GetOriginY() - GetHeight() / 2.f,
					GetOriginX() - GetWidth() / 2.f, GetOriginY() + GetHeight() / 2.f);

				float area2 = triangleArea(Object->GetOriginX(), Object->GetOriginY(),
					GetOriginX() + GetWidth() / 2.f, GetOriginY() - GetHeight() / 2.f,
					GetOriginX() + GetWidth() / 2.f, GetOriginY() + GetHeight() / 2.f);

				float length = baseLength(GetOriginX() - GetWidth() / 2.f, GetOriginY() - GetHeight() / 2.f,
					GetOriginX() - GetWidth() / 2.f, GetOriginY() + GetHeight() / 2.f);

				xNormal = area1 < area2 ? triangleHeight(area1, length) : triangleHeight(area2, length);
			}

			// Change ball's velocity 
			if (yNormal < Object->GetHeight() / 2.f)
			{
				ChangeY();
			}
			else if (xNormal < Object->GetWidth() / 2.f)
			{
				ChangeX();
			}
		}
	}

	float UBall::GetOriginX() const
	{
		return Sprite.getOrigin().x;
	}

	float UBall::GetOriginY() const
	{
		return Sprite.getOrigin().y;
	}

	float UBall::GetWidth() const
	{
		return Size;
	}

	float UBall::GetHeight() const
	{
		return Size;
	}
}