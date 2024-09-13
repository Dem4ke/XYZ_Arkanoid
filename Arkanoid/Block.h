#pragma once

#include "GameObject.h"
#include "Resources.h"
#include "Math.h"

namespace ArkanoidGame {
	class Block : public GameObject {
	public:
		Block(Resources& resources, sf::RenderWindow& window);
		virtual ~Block() {}

		void init(float size, float speed) override;
		void update(const float& deltaTime) override;
		void draw() override;

	private:
		sf::Vector2f position_;

		sf::Sprite sprite_;

		Resources& resources_;
		sf::RenderWindow& window_;
	};
}