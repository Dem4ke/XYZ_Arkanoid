#pragma once

#include "GameStates.h"
#include "Resources.h"
#include "Player.h"
#include "Apple.h"
#include "Wall.h"

#include <cstdlib>

namespace SnakeGame {

	enum class objectType : short {
		none = 0,
		snakeHead,
		snakeBody,
		normalApple,
		poisonedApple,
		wall,
	};

	class CellOfField {
	public:
		CellOfField(float height, float width);

		void setSpritePosition(float x, float y);

		void setObject(sf::Texture& texture, objectType object);
		void clear();
		void rotateSprite(float rotateDegree);

		sf::Sprite getObjectSprite() const;
		objectType getObjectType() const;
		
	private:
		float height_ = 0.f;
		float width_ = 0.f;

		objectType indicator = objectType::none;

		sf::Sprite sprite_;
	};

	class GameField {
	public:
		GameField(Resources& resources, GameState& gameState);

		void init();
		void reset();
		void update(const float& deltaTime);

		int getFieldSize() const;
		sf::Sprite getSprite(int index) const;

	private:
		void cellInfoCheck();
		void setPerimeterCellSprite();
		void setAppleCellSprite();
		int getRandomAvaliblePosition();

		float defTimer_ = 100.f;
		float timer_ = 0.f;
		int cols_ = 40;
		int rows_ = 30;

		std::vector<CellOfField> field_;

		Resources& resources_;
		GameState& gameState_;

		Player player_;
		Apple apple_;
	};

	void DrawGameField(GameField& gameField, sf::RenderWindow& window);
}