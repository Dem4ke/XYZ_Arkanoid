#include <cassert>
#include "Platform.h"
#include "../../../Math/Math.h"
#include "../../../Settings/Settings.h"

namespace Arkanoid
{
	UPlatform::UPlatform(const sf::Vector2f& InputedPosition)
		: Position(InputedPosition)
	{
		// Load texture
		bool bIsLoaded = Texture.loadFromFile("Resources/MainTextures/platform.png");
		assert(bIsLoaded);

		Width *= SETTINGS.GetScaleFactor().X;
		Height *= SETTINGS.GetScaleFactor().Y;
		Speed *= SETTINGS.GetScaleFactor().Y;

		Sprite.setTexture(Texture);
		Sprite.setTextureRect(TextureRect);

		Math::SetSize(Sprite, Width, Height);
		Math::SetRelativeOrigin(Sprite, 0.5f, 0.5f);

		// Set start position
		Position.y -= Height / 2.f;
		Sprite.setPosition(Position);
	}

	UPlatform::UPlatform(const UPlatform& Platform)
		: Width(Platform.Width)
		, Height(Platform.Height)
		, Speed(Platform.Speed)
		, ObjectType(Platform.ObjectType)
		, TextureRect(Platform.TextureRect)
		, Position(Platform.Position)
		, Texture(Platform.Texture)
		, Sprite(Platform.Sprite)
	{}

	void UPlatform::Update(const float& DeltaTime) 
	{
		// Change velocity direction of platform while player pressed key
		if (sf::Keyboard::isKeyPressed(Button.RightKey)) {
			if ((Position.x + GetWidth() / 2.f) >= SETTINGS.GetScreenWidth()) {
				// Stop platform
				Position.x += Speed * 0;
			}
			else {
				// Platform goes to right
				Position.x += Speed * DeltaTime;
			}
		}
		else if (sf::Keyboard::isKeyPressed(Button.LeftKey)) {
			if ((Position.x - GetWidth() / 2.f) <= 0) {
				// Stop platform
				Position.x += Speed * 0;
			}
			else {
				// Platform goes to left
				Position.x -= Speed * DeltaTime;
			}
		}

		// Update platform's position
		Sprite.setPosition(Position);
	}

	void UPlatform::Draw(sf::RenderWindow& Window)
	{
		Window.draw(Sprite);
	}

	bool UPlatform::CheckCollision(std::shared_ptr<IGameObject> Object, EObjectType Type) 
	{
		return false;
	}

	void UPlatform::Hit() {}

	float UPlatform::GetOriginX() const
	{
		return Position.x;
	}

	float UPlatform::GetOriginY() const
	{
		return Position.y;
	}

	float UPlatform::GetWidth() const
	{
		return Width;
	}

	float UPlatform::GetHeight() const
	{
		return Height;
	}

	EObjectType UPlatform::GetObjectType() const
	{
		return ObjectType;
	}

	bool UPlatform::IsDestroyed() const
	{
		return false;
	}
	std::shared_ptr<IGameObject> UPlatform::clone() const
	{
		return std::make_shared<UPlatform>(*this);
	}
}