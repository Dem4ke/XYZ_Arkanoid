#pragma once

#include <SFML/Graphics.hpp>
#include "../IGameObject.h"
#include "../../CButton.h"

namespace Arkanoid
{
	class UPlatform final : public IGameObject
	{
	public:
		UPlatform(const sf::Vector2f& InputedPosition);
		UPlatform(const UPlatform& Platform);
		~UPlatform() = default;

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
		
	private:
		float Width = 140.f;			// Width of the platform
		float Height = 30.f;			// Height of the platform
		float Speed = 400.f;			// Speed of the platform

		EObjectType ObjectType = EObjectType::Platform;	// Type of current game object
		sf::IntRect TextureRect{ 33, 0, 30, 7 };		// Rectangle coordinates on the blocks texture 

		sf::Vector2f Position;			// Position of the platform on screen
		sf::Texture Texture;			// Texture of the platform
		sf::Sprite Sprite;				// Sprite to draw


		CButton Button;					// Keys to work with the game
	};
}