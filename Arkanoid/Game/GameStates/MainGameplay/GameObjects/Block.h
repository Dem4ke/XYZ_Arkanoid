#pragma once

#include <SFML/Graphics.hpp>
#include "../IGameObject.h"

namespace Arkanoid
{
	class UBlock : public IGameObject
	{
	public:
		UBlock(const sf::Vector2f& Position, const sf::Texture& Texture);
		virtual ~UBlock() = default;

		virtual void Update(const float& deltaTime) override;
		void Draw(sf::RenderWindow& Window) override;

		virtual int CheckCollision(std::shared_ptr<IGameObject> Object) override;

		float GetOriginX() const override;
		float GetOriginY() const override;
		float GetWidth() const override;
		float GetHeight() const override;

	protected:
		int Health = 1;									// Count of hits to destroy block
		
		float Width = 60.f;								// Width of block
		float Height = 20.f;							// Height of block

		sf::IntRect TextureRect{ 1, 1, 23, 9 };			// Rectangle coordinates on the blocks texture 
		sf::Vector2f CurrentPosition;					// Position of block on screen
		sf::Sprite Sprite;								// Sprite to draw
	};

	class UThreeHitBlock final : public UBlock
	{
	public:
		UThreeHitBlock(const sf::Vector2f& Position, const sf::Texture& Texture);
		~UThreeHitBlock() = default;

		void Update(const float& DeltaTime) override;

	private:
		int Health = 3;									// Count of hits to destroy block

		sf::IntRect TextureRect{ 53, 1, 23, 9 };		// Rectangle coordinates on the blocks texture 
		sf::IntRect TextureRect1Hit{ 53, 14, 23, 9 };	// Rectangle coordinates on the blocks texture 
		sf::IntRect TextureRect2Hit{ 53, 25, 23, 9 };	// Rectangle coordinates on the blocks texture 
	};

	class UUnbreakableBlock final : public UBlock
	{
	public:
		UUnbreakableBlock(const sf::Vector2f& Position, const sf::Texture& Texture);
		~UUnbreakableBlock() = default;

	private:
		unsigned int Health = 40000;

		sf::IntRect TextureRect{ 1, 1, 23, 9 };			// Rectangle coordinates on the blocks texture 
	};
}