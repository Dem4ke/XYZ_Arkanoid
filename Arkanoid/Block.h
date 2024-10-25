#pragma once

#include "GameObject.h"
#include "Resources.h"
#include "Math.h"

namespace ArkanoidGame {

	class Block : public GameObject {
	public:
		Block(Resources& resources, sf::RenderWindow& window);

		void init(float size, float speed, sf::Vector2f position) override;
		void update(const float& deltaTime) override;
		void draw() override;

		int checkCollide(std::shared_ptr<GameObject> object) override;
		virtual int getCost() const;

		bool isCrashed() const;

		float getOriginX() const override;
		float getOriginY() const override;
		float getWidth() const override;
		float getHeight() const override;

	protected:
		float width_ = 0.f;
		float height_ = 0.f;

		int health_ = 1;
		int cost_ = 1;

		sf::IntRect textureRect_{ 1, 1, 23, 9 };
		sf::Vector2f position_;
		sf::Sprite sprite_;

		Resources& resources_;
		sf::RenderWindow& window_;
	};

	class ThreeHitsBlock : public Block {
	public:
		ThreeHitsBlock(Resources& resources, sf::RenderWindow& window);
	
		void init(float size, float speed, sf::Vector2f position) override;
		void update(const float& deltaTime) override;

		int getCost() const override;

	private:
		int cost_ = 3;

		sf::IntRect textureRect1_{ 53, 1, 23, 9 };
		sf::IntRect textureRect2_{ 53, 14, 23, 9 };
		sf::IntRect textureRect3_{ 53, 25, 23, 9 };
	};
}