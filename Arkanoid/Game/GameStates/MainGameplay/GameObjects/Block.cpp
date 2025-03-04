#include <cassert>
#include "Block.h"
#include "../Observer/Observer.h"
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

	/*//////////////////////////////////*/
	/*                                  */
	/*	     GAME OBJECT METHODS        */
	/*                                  */
	/*//////////////////////////////////*/

	void UBlock::Update(const float& DeltaTime) {}

	void UBlock::Draw(sf::RenderWindow& Window)
	{
		Window.draw(Sprite);
	}

	bool UBlock::CheckCollision(std::shared_ptr<IGameObject> Object, EObjectType Type) 
	{
		return false;
	}

	void UBlock::Hit() 
	{
		--Health;
		if (Health <= 0)
		{
			Notify();
		}
	}

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

	bool UBlock::IsDestroyed() const
	{
		if (Health <= 0)
		{
			return true;
		}

		return false;
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	       SUBJECT METHODS          */
	/*                                  */
	/*//////////////////////////////////*/

	void UBlock::Attach(std::shared_ptr<IBlockObserver> Observer)
	{
		Observers.push_back(Observer);
	}

	void UBlock::Detach(std::shared_ptr<IBlockObserver> Observer)
	{
		Observers.erase(std::remove(Observers.begin(), Observers.end(), Observer), Observers.end());
	}

	void UBlock::Notify()
	{
		for (auto& i : Observers)
		{
			i->BlockBroken(Cost);
		}
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	       THREE HIT BLOCK          */
	/*                                  */
	/*//////////////////////////////////*/

	UThreeHitBlock::UThreeHitBlock(const sf::Vector2f& InputedPosition)
		: UBlock(InputedPosition)
	{
		Sprite.setTextureRect(TextureRect);
	}

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

	void UThreeHitBlock::Hit()
	{
		--Health;
		if (Health <= 0)
		{
			Notify();
		}
	}

	bool UThreeHitBlock::IsDestroyed() const
	{
		if (Health <= 0)
		{
			return true;
		}

		return false;
	}

	/*//////////////////////////////////*/
	/*                                  */
	/*	      UNBREAKABLE BLOCK         */
	/*                                  */
	/*//////////////////////////////////*/

	UUnbreakableBlock::UUnbreakableBlock(const sf::Vector2f& InputedPosition)
		: UBlock(InputedPosition)
	{
		Sprite.setColor(sf::Color::White);
	}

	void UUnbreakableBlock::Update(const float& DeltaTime) {}

	void UUnbreakableBlock::Hit() {}

	bool UUnbreakableBlock::IsDestroyed() const
	{
		return false;
	}
}