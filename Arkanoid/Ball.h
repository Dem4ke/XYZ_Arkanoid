#pragma once

#include "GameObject.h"
#include "Resources.h"
#include "Math.h"

namespace ArkanoidGame {

	class Ball final : public GameObject {
	public:
		Ball(Resources& resources, sf::RenderWindow& window);

		void init(float size, float speed, sf::Vector2f position) override;
		void update(const float& deltaTime) override;
		void changeAngle(float newAngle);
		void draw() override;

		void needToChangeX();
		void needToChangeY();
		void changeX();
		void changeY();
		
		int changedWay();
		int checkCollide(std::shared_ptr<GameObject> object) override;

		float getOriginX() const override;
		float getOriginY() const override;
		float getWidth() const override;
		float getHeight() const override;

		bool isOutOfPlayground() const;

	private:
		float size_ = 0.f;
		float speed_ = 0.f;
		float angle_ = 0.f;

		bool isNeedToChangeX_ = false;
		bool isNeedToChangeY_ = false;
		bool isOutOfPlayground_ = false;

		sf::Vector2f direction_;
		sf::Vector2f position_;	

		sf::CircleShape circle_;

		Resources& resources_;
		sf::RenderWindow& window_;
	};
}
