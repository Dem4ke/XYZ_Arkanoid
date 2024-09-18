#pragma once

#include "GameObject.h"
#include "Resources.h"
#include "Math.h"

namespace ArkanoidGame {

	class Platform final : public GameObject {
	public:
		Platform(Resources& resources, sf::RenderWindow& window);
		virtual ~Platform() {}

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
		const float height_ = 20.f;
		float speed_ = 0.f;

		sf::Vector2f position_;

		sf::RectangleShape rectangle_;

		sf::Keyboard::Key leftKey_ = sf::Keyboard::Left;
		sf::Keyboard::Key rightKey_ = sf::Keyboard::Right;

		Resources& resources_;
		sf::RenderWindow& window_;
	};
}

