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

	void UBlock::Update(const float& DeltaTime) {}

	void UBlock::Draw(sf::RenderWindow& Window)
	{
		Window.draw(Sprite);
	}

	void UBlock::CheckCollision(std::shared_ptr<IGameObject> Object, EObjectType Type) {}

	float UBlock::GetOriginX() const
	{
		return Position.x;
	}

	float UBlock::GetOriginY() const
	{
		return Position.y;
	}

	float UBlock::GetWidth() const
	{
		return Width;
	}

	float UBlock::GetHeight() const
	{
		return Height;
	}

	EObjectType UBlock::GetObjectType() const
	{
		return Type;
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