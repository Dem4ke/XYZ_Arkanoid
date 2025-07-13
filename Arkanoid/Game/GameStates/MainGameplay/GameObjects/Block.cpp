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

	UBlock::UBlock(const UBlock& Block)
		: Health(Block.Health)
		, Cost(Block.Cost)
		, Width(Block.Width)
		, Height(Block.Height)
		, Type(Block.Type)
		, Position(Block.Position)
		, Texture(Block.Texture)
		, Sprite(Block.Sprite)
		, TextureRect(Block.TextureRect)
		, Observers(Block.Observers)
	{}

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

	std::shared_ptr<IGameObject> UBlock::clone() const
	{
		return std::make_shared<UBlock>(*this);
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
			i->BlockBroken(Cost, Position);
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

	UThreeHitBlock::UThreeHitBlock(const UThreeHitBlock& Block)
		: UBlock(Block)
		, Health(Block.Health)
		, Cost(Block.Cost)
		, Type(Block.Type)
		, TextureRect(Block.TextureRect)
		, TextureRect1Hit(Block.TextureRect1Hit)
		, TextureRect2Hit(Block.TextureRect2Hit)
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

	std::shared_ptr<IGameObject> UThreeHitBlock::clone() const
	{
		return std::make_shared<UThreeHitBlock>(*this);
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

	UUnbreakableBlock::UUnbreakableBlock(const UUnbreakableBlock& Block)
		: UBlock(Block)
		, Health(Block.Health)
		, Cost(Block.Cost)
		, Type(Block.Type)
		, TextureRect(Block.TextureRect)
	{}

	void UUnbreakableBlock::Update(const float& DeltaTime) {}

	void UUnbreakableBlock::Hit() {}

	bool UUnbreakableBlock::IsDestroyed() const
	{
		return false;
	}

	std::shared_ptr<IGameObject> UUnbreakableBlock::clone() const
	{
		return std::make_shared<UUnbreakableBlock>(*this);
	}
}