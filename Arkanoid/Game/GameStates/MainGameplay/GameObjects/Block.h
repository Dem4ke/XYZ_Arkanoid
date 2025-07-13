#pragma once

#include <SFML/Graphics.hpp>
#include "../IGameObject.h"
#include "../Observer/Subject.h"

namespace Arkanoid
{
	class UBlock : public IGameObject, public IBlockSubject
	{
	public:
		UBlock(const sf::Vector2f& InputedPosition);
		UBlock(const UBlock& Block);
		virtual ~UBlock() = default;

		virtual void Update(const float& DeltaTime) override;
		void Draw(sf::RenderWindow& Window) override;
		bool CheckCollision(std::shared_ptr<IGameObject> Object, EObjectType Type) override;
		virtual void Hit() override;

		float GetOriginX() const override;
		float GetOriginY() const override;
		float GetWidth() const override; 
		float GetHeight() const override;

		EObjectType GetObjectType() const override;
		virtual bool IsDestroyed() const override;

		virtual std::shared_ptr<IGameObject> clone() const override;

		void Attach(std::shared_ptr<IBlockObserver> Observer) override;
		void Detach(std::shared_ptr<IBlockObserver> Observer) override;
		void Notify() override;

	protected:
		int Health = 1;									// Count of hits to destroy block
		int Cost = 1;									// Cost of block in the score points

		float Width = 125.f;							// Width of the block
		float Height = 40.f;							// Height of the block

		EObjectType Type = EObjectType::SimpleBlock;	// Type of current game object

		sf::Vector2f Position;							// Position of the block on screen
		sf::Texture Texture;							// Texture of the block
		sf::Sprite Sprite;								// Sprite to draw
		sf::IntRect TextureRect{ 1, 1, 23, 9 };			// Rectangle coordinates on the block's texture 

		std::vector<std::shared_ptr<IBlockObserver>> Observers;// Vector of observers
	};

	class UThreeHitBlock final : public UBlock
	{
	public:
		UThreeHitBlock(const sf::Vector2f& InputedPosition);
		UThreeHitBlock(const UThreeHitBlock& Block);
		~UThreeHitBlock() = default;

		void Update(const float& DeltaTime) override;
		void Hit() override;
		bool IsDestroyed() const override;

		std::shared_ptr<IGameObject> clone() const override;

	private:
		int Health = 3;									// Count of hits to destroy block
		int Cost = 3;									// Cost of block in the score points

		EObjectType Type = EObjectType::ThreeHitBlock;	// Type of current game object

		sf::IntRect TextureRect{ 53, 1, 23, 9 };		// Rectangle coordinates on the blocks texture 
		sf::IntRect TextureRect1Hit{ 53, 14, 23, 9 };	// Rectangle coordinates on the blocks texture 
		sf::IntRect TextureRect2Hit{ 53, 25, 23, 9 };	// Rectangle coordinates on the blocks texture 
	};

	class UUnbreakableBlock final : public UBlock
	{
	public:
		UUnbreakableBlock(const sf::Vector2f& InputedPosition);
		UUnbreakableBlock(const UUnbreakableBlock& Block);
		~UUnbreakableBlock() = default;

		void Update(const float& DeltaTime) override;
		void Hit() override;
		bool IsDestroyed() const override;

		std::shared_ptr<IGameObject> clone() const override;

	private:
		int Health = 4;
		int Cost = 0;									// Cost of block in the score points

		EObjectType Type = EObjectType::UnbreackableBlock;	// Type of current game object

		sf::IntRect TextureRect{ 1, 1, 23, 9 };			// Rectangle coordinates on the blocks texture 
	};
}