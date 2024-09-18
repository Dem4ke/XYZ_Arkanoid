#pragma once

#include "GameObject.h"
#include "Resources.h"
#include "Math.h"

namespace ArkanoidGame {

	class Block : public GameObject {
	public:
		Block(Resources& resources, sf::RenderWindow& window);
		virtual ~Block() {}

		void init(float size, float speed, sf::Vector2f position) override;
		void update(const float& deltaTime) override;
		void draw() override;

		int checkCollide(std::shared_ptr<GameObject> object) override;

		float getOriginX() const override;
		float getOriginY() const override;
		float getWidth() const override;
		float getHeight() const override;

	private:
		float width_ = 0.f;
		float height_ = 0.f;
		bool isCrashed_ = false;

		sf::Vector2f position_;
		sf::RectangleShape rectangle_;

		Resources& resources_;
		sf::RenderWindow& window_;
	};
}