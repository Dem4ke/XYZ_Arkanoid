#include <cassert>
#include "Block.h"
#include "../../../Math/Math.h"
#include "../../../Settings/Settings.h"

namespace Arkanoid
{
	UBlock::UBlock(const sf::Vector2f& InputedPosition) 
	: Position(InputedPosition)
	{
		// Load texture
		bool bIsLoaded = Texture.loadFromFile("Resources/MainTextures/blocks_bricks.png");
		assert(bIsLoaded);

		Width *= SETTINGS.GetScaleFactor().X;
		Height *= SETTINGS.GetScaleFactor().Y;

		Sprite.setTexture(Texture);
		Sprite.setTextureRect(TextureRect);
		Sprite.setColor(Math::GetRandomColor());
		
		Math::SetSize(Sprite, Width, Height);
		Math::SetRelativeOrigin(Sprite, 0.5f, 0.5f);

		Sprite.setPosition(Position);
	}

	void UBlock::Update(const float& deltaTime) {}

	void UBlock::Draw(sf::RenderWindow& Window)
	{
		Window.draw(Sprite);
	}

	int UBlock::CheckCollision(std::shared_ptr<IGameObject> Object)
	{
		float xNormal = Object->GetHeight() + 1.f;
		float yNormal = Object->GetHeight() + 1.f;

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

		if (yNormal < Object->GetWidth() / 2.f) 
		{
			--Health;
			return 1;
		}
		else if (xNormal < Object->GetWidth() / 2.f) 
		{
			--Health;
			return 2;
		}

		return 0;
	}

	float UBlock::GetOriginX() const
	{
		return Sprite.getOrigin().x;
	}

	float UBlock::GetOriginY() const
	{
		return Sprite.getOrigin().y;
	}

	float UBlock::GetWidth() const
	{
		return Width;
	}

	float UBlock::GetHeight() const
	{
		return Height;
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	       THREE HIT BLOCK          */
	/*                                  */
	/*//////////////////////////////////*/

	UThreeHitBlock::UThreeHitBlock(const sf::Vector2f& InputedPosition)
	: UBlock(InputedPosition)
	{}

	void UThreeHitBlock::Update(const float& DeltaTime)
	{
		if (Health == 2) 
		{
			Sprite.setTextureRect(TextureRect1Hit);
		}
		else if (Health == 1) 
		{
			Sprite.setTextureRect(TextureRect2Hit);
		}
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	      UNBREAKABLE BLOCK         */
	/*                                  */
	/*//////////////////////////////////*/

	UUnbreakableBlock::UUnbreakableBlock(const sf::Vector2f& InputedPosition)
	: UBlock(InputedPosition)
	{}

	void UUnbreakableBlock::Update(const float& DeltaTime)
	{
		Health = 4;
	}
}