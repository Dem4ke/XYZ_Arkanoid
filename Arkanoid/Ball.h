#pragma once

#include "GameObject.h"
#include "Resources.h"
#include "Math.h"

namespace ArkanoidGame {

	class Ball final : public GameObject {
	public:
		Ball(Resources& resources, sf::RenderWindow& window);

		void init(float size = 20.f, float speed = 600.f) override;
		void update(const float& deltaTime) override;
		void changeAngle(float newAngle);
		void draw() override;

		float getSize() const;
		float centerX() const;
		float bottomY() const;
		bool isOutOfPlayground() const;

	private:
		float size_ = 0.f;
		float speed_ = 0.f;
		float angle_ = 0.f;

		bool isOutOfPlayground_ = 0;

		sf::Vector2f direction_;
		sf::Vector2f position_;	

		sf::CircleShape circle_;

		Resources& resources_;
		sf::RenderWindow& window_;
	};
}
