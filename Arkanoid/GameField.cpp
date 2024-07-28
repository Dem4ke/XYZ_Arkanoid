#include "GameField.h"

namespace SnakeGame {

	// CELL

	CellOfField::CellOfField(float height, float width) :
		height_(height), width_(width) {}

	// Set sprite's position
	void CellOfField::setSpritePosition(float x, float y) {
		sprite_.setPosition(x, y);
	}

	void CellOfField::clear() {
		SetSpriteSize(sprite_, 0.f, 0.f);

		// Cell is empty
		indicator = objectType::none;
	}

	void CellOfField::rotateSprite(float rotateDegree) {
		sprite_.setRotation(rotateDegree);
	}
	// Set sprite's texute, size and origin
	void CellOfField::setObject(sf::Texture& texture, objectType object) {
		sprite_.setTexture(texture);
		SetSpriteSize(sprite_, height_, width_);
		SetSpriteRelativeOrigin(sprite_, 0.5f, 0.5f);

		// Cell is fill
		indicator = object;
	}

	sf::Sprite CellOfField::getObjectSprite() const { return sprite_; }

	objectType CellOfField::getObjectType() const { return indicator; }

	//----------------------------------------------------------
	// GAME FIELD

	GameField::GameField(Resources& resources, GameState& gameState) :
		resources_(resources), player_(),
		apple_(), gameState_(gameState) {

		init(); // init game field cells
	}

	// Initialization of game field
	// Split playable screen on cells and put them in vector	
	void GameField::init() {
		// reserve vector capacity
		int end = rows_ * cols_;
		field_.reserve(end);

		// get height and width of any cell
		float height = resources_.getWindowHeight() / rows_;
		float width = resources_.getWindowWidth() / cols_;

		// Make a counters to count created cells
		int countOfCols = 0;
		int countOfRows = 0;

		// Initialization of all cells 
		for (int i = 0; i < end; ++i) {
			CellOfField cell(height, width);
			
			// must count cols and rows to dont go out of window borders
			// because of screen is matrix of cells
			// cols' counter have to be less than cols
			// rows' counter have to be less than rows

			// Sprite position is in center of a cell
			cell.setSpritePosition(countOfCols * width + 0.5f * width, 
								countOfRows * height + 0.5f * height);
			field_.push_back(cell);

			++countOfCols;
			if (countOfCols == cols_) {
				countOfCols = 0;
				++countOfRows;
			}

			// Initialiazation of the player
			switch (gameState_.getCurrentDiffLvl()) {
			case DifficultyLevel::Easy: {
				player_.init(1);
				apple_.init(2);
				break;
			}
			case DifficultyLevel::HarderThanEasy: {
				player_.init(1.3);
				apple_.init(4);
				break;
			}
			case DifficultyLevel::Medium: {
				player_.init(1.8);
				apple_.init(6);
				break;
			}
			case DifficultyLevel::LessThanHard: {
				player_.init(2.1);
				apple_.init(8);
				break;
			}
			case DifficultyLevel::Hard: {
				player_.init(2.5);
				apple_.init(10);
				break;
			}
			}
		}
	}

	void GameField::reset() {
		// Initialization of filed and interactive objects
		init();

		// Set walls 
		setPerimeterCellSprite();
	}

	void GameField::update(const float& deltaTime) {
		// Delay to move in another cell
		timer_ -= (player_.getSpeed() * deltaTime);

		// Change snake's head direction
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			if (player_.getDirection() != PlayerDirection::Left) {
				player_.moveRight();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			if (player_.getDirection() != PlayerDirection::Down) {
				player_.moveUp();
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			if (player_.getDirection() != PlayerDirection::Right) {
				player_.moveLeft();

			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			if (player_.getDirection() != PlayerDirection::Up) {
				player_.moveDown();
			}
		}

		if (timer_ <= 0) {

			// Change position of snake's head sprite 
			switch (player_.getDirection()) {
			case PlayerDirection::Up: {

				// Check info about cell under player's head (is that cell a body)
				cellInfoCheck();

				// Clear all cells 
				for (int i = 0, end = player_.getSize(); i < end; ++i) {
					field_[player_.getPositionOnField(i)].clear();
				}

				// Move player on next position
				player_.setPositionOnField(player_.getPositionOnField(0) - cols_);

				// Check info about cell under player's head
				cellInfoCheck();

				// Set head's sprite on new position
				field_[player_.getPositionOnField(0)].setObject(resources_.snakeHeadTexture, objectType::snakeHead);
				field_[player_.getPositionOnField(0)].rotateSprite(270.f);

				// Set bodies' sprites on new position
				for (int i = 1, end = player_.getSize(); i < end; ++i) {
					field_[player_.getPositionOnField(i)].setObject(resources_.snakeBodyTexture, objectType::snakeBody);
				}

				timer_ = defTimer_;

				break;
			}
			case PlayerDirection::Down: {

				// Check info about cell under player's head (is that cell a body)
				cellInfoCheck();

				// Clear all cells 
				for (int i = 0, end = player_.getSize(); i < end; ++i) {
					field_[player_.getPositionOnField(i)].clear();
				}

				// Move player on next position
				player_.setPositionOnField(player_.getPositionOnField(0) + cols_);

				// Check info about cell under player's head
				cellInfoCheck();

				// Set head's sprite on new position
				field_[player_.getPositionOnField(0)].setObject(resources_.snakeHeadTexture, objectType::snakeHead);
				field_[player_.getPositionOnField(0)].rotateSprite(90.f);

				// Set bodies' sprites on new position
				for (int i = 1, end = player_.getSize(); i < end; ++i) {
					field_[player_.getPositionOnField(i)].setObject(resources_.snakeBodyTexture, objectType::snakeBody);
				}

				timer_ = defTimer_;

				break;
			}
			case PlayerDirection::Right: {

				// Check info about cell under player's head (is that cell a body)
				cellInfoCheck();

				// Clear all cells 
				for (int i = 0, end = player_.getSize(); i < end; ++i) {
					field_[player_.getPositionOnField(i)].clear();
				}

				// Move player on next position
				player_.setPositionOnField(player_.getPositionOnField(0) + 1);

				// Check info about cell under player's head
				cellInfoCheck();

				// Set head's sprite on new position
				field_[player_.getPositionOnField(0)].setObject(resources_.snakeHeadTexture, objectType::snakeHead);
				field_[player_.getPositionOnField(0)].rotateSprite(0.f);

				// Set bodies' sprites on new position
				for (int i = 1, end = player_.getSize(); i < end; ++i) {
					field_[player_.getPositionOnField(i)].setObject(resources_.snakeBodyTexture, objectType::snakeBody);
				}

				timer_ = defTimer_;

				break;
			}
			case PlayerDirection::Left: {

				// Check info about cell under player's head (is that cell a body)
				cellInfoCheck();

				// Clear all cells 
				for (int i = 0, end = player_.getSize(); i < end; ++i) {
					field_[player_.getPositionOnField(i)].clear();
				}

				// Move player on next position
				player_.setPositionOnField(player_.getPositionOnField(0) - 1);

				// Check info about cell under player's head
				cellInfoCheck();

				// Set head's sprite on new position
				field_[player_.getPositionOnField(0)].setObject(resources_.snakeHeadTexture, objectType::snakeHead);
				field_[player_.getPositionOnField(0)].rotateSprite(180.f);

				// Set bodies' sprites on new position
				for (int i = 1, end = player_.getSize(); i < end; ++i) {
					field_[player_.getPositionOnField(i)].setObject(resources_.snakeBodyTexture, objectType::snakeBody);
				}

				timer_ = defTimer_;

				break;
			}
			}
		}
		
		// Create apple in random position on screen
		if (!apple_.isAppleExists()) {
			setAppleCellSprite();
		}
	}

	int GameField::getFieldSize() const { return cols_ * rows_; }

	sf::Sprite GameField::getSprite(int index) const {
		return field_[index].getObjectSprite();
	}

	// PRIVATE TOOLS
	
	// Check cell info which player's head reach
	void GameField::cellInfoCheck() {
		if (field_[player_.getPositionOnField(0)].getObjectType() == objectType::wall) { 
			GameOverSound(resources_);
			gameState_.pushGameState(GameStateType::GameOverPopUp);
		}
		else if (field_[player_.getPositionOnField(0)].getObjectType() == objectType::poisonedApple) {

		}
		else if (field_[player_.getPositionOnField(0)].getObjectType() == objectType::snakeBody) {
			GameOverSound(resources_);
			gameState_.pushGameState(GameStateType::GameOverPopUp);
		}
		else if (field_[player_.getPositionOnField(0)].getObjectType() == objectType::normalApple) {
			AppleEatenSound(resources_);
			gameState_.scoreIncrease(apple_.getCost()); // update player's score
			apple_.setStatus(false);					// delete apple from field
			player_.sizeIncrease();						// update player size
		}
	}

	// Set sprites on perimeter
	void GameField::setPerimeterCellSprite() {
		// Make a counters to count cells
		int countOfCols = 0;
		int countOfRows = 0;

		// Set walls around field
		for (int i = 0, end = getFieldSize(); i < end; ++i, ++countOfCols) {
			if (countOfCols == cols_) {
				countOfCols = 0;
				++countOfRows;
			}

			if (countOfCols == 0) {
				field_[i].setObject(resources_.wallTexture, objectType::wall);
				field_[i].rotateSprite(90.f);
			}
			else if (countOfCols == cols_ - 1) {
				field_[i].setObject(resources_.wallTexture, objectType::wall);
				field_[i].rotateSprite(270.f);
			}
			else if (countOfRows == 0) {
				field_[i].setObject(resources_.wallTexture, objectType::wall);
				field_[i].rotateSprite(180.f);
			}
			else if (countOfRows == rows_ - 1) {
				field_[i].setObject(resources_.wallTexture, objectType::wall);
				field_[i].rotateSprite(0.f);
			}
			else {
				field_[i].clear();
			}
		}
	}

	void GameField::setAppleCellSprite() {
		// Set position to apple
		apple_.setPositionOnField(getRandomAvaliblePosition());

		// Set apple's sprite in avalible position
		field_[apple_.getPositionOnField()].setObject(resources_.appleTexture, objectType::normalApple);
		field_[apple_.getPositionOnField()].rotateSprite(0.f);

		// Change apple's signature to exists
		apple_.setStatus(true);
	}

	int GameField::getRandomAvaliblePosition() {
		int position = 0;

		while (true) {
			position = rand() / (float)RAND_MAX * getFieldSize();

			if (field_[position].getObjectType() == objectType::none) {
				break;
			}
		}

		return position;
	}

	//----------------------------------------------------------
	// FUNCTIONS

	void DrawGameField(GameField& gameField, sf::RenderWindow& window) {
		for (int i = 0, end = gameField.getFieldSize(); i < end; ++i) {
			window.draw(gameField.getSprite(i));
		}
	}
}