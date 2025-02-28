#pragma once

#include <SFML/Graphics.hpp>
#include "../IGameObject.h"

namespace Arkanoid
{
	class UBlock : public IGameObject
	{
	public:
		UBlock(const sf::Vector2f& InputedPosition);
		virtual ~UBlock() = default;

		virtual void Update(const float& DeltaTime) override;
		void Draw(sf::RenderWindow& Window) override;

		void CheckCollision(std::shared_ptr<IGameObject> Object, EObjectType Type) override;

		float GetOriginX() const override;
		float GetOriginY() const override;
		float GetWidth() const override; 
		float GetHeight() const override;

		EObjectType GetObjectType() const override;

	protected:
		int Health = 1;									// Count of hits to destroy block
		
		float Width = 125.f;							// Width of the block
		float Height = 40.f;							// Height of the block

		EObjectType Type = EObjectType::SimpleBlock;	// Type of current game object

		sf::Vector2f Position;							// Position of the block on screen
		sf::Texture Texture;							// Texture of the block
		sf::Sprite Sprite;								// Sprite to draw
		sf::IntRect TextureRect{ 1, 1, 23, 9 };			// Rectangle coordinates on the block's texture 
	};

	class UThreeHitBlock final : public UBlock
	{
	public:
		UThreeHitBlock(const sf::Vector2f& InputedPosition);
		~UThreeHitBlock() = default;

		void Update(const float& DeltaTime) override;

	private:
		int Health = 3;									// Count of hits to destroy block

		EObjectType Type = EObjectType::ThreeHitBlock;	// Type of current game object

		sf::IntRect TextureRect{ 53, 1, 23, 9 };		// Rectangle coordinates on the blocks texture 
		sf::IntRect TextureRect1Hit{ 53, 14, 23, 9 };	// Rectangle coordinates on the blocks texture 
		sf::IntRect TextureRect2Hit{ 53, 25, 23, 9 };	// Rectangle coordinates on the blocks texture 
	};

	class UUnbreakableBlock final : public UBlock
	{
	public:
		UUnbreakableBlock(const sf::Vector2f& InputedPosition);
		~UUnbreakableBlock() = default;

		void Update(const float& DeltaTime) override;

	private:
		int Health = 4;

		EObjectType Type = EObjectType::UnbreackableBlock;	// Type of current game object

		sf::IntRect TextureRect{ 1, 1, 23, 9 };			// Rectangle coordinates on the blocks texture 
	};
}