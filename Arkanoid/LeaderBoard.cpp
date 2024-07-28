#include "LeaderBoard.h"

namespace SnakeGame {

	// LEADER BOARD

	void LeaderBoard::init(std::string menuName, float buttonSize, int drawablePositions, GameState& gameState) {
		posX_ = resources_.getWindowWidth() / 2.f;
		posY_ = resources_.getWindowHeight() / 5.f;
		buttonSize_ = buttonSize;
		drawablePositions_ = drawablePositions;
		shortDrawablePos_ = drawablePositions - 3;

		// Initialization of a menu name
		menuName_.setFont(resources_.font);
		menuName_.setCharacterSize(buttonSize_ * 1.5f);
		menuName_.setFillColor(mainButtonColor_);
		menuName_.setString(menuName);
		menuName_.setOrigin(sf::Vector2f(menuName_.getGlobalBounds().width / 2.f, menuName_.getGlobalBounds().height / 2.f));
		menuName_.setPosition(posX_, posY_ - buttonSize_);

		// Initialization of players' names
		playerName_.setFont(resources_.font);
		playerName_.setCharacterSize(buttonSize_);
		playerName_.setFillColor(mainButtonColor_);

		// Initialization of players' score
		playerScore_.setFont(resources_.font);
		playerScore_.setCharacterSize(buttonSize_);
		playerScore_.setFillColor(mainButtonColor_);

		backgroundSprite_.setTexture(resources_.mainMenuBackground);

		SetSpriteSize(backgroundSprite_, resources_.getWindowWidth(), resources_.getWindowHeight());

		// Get leader board from file
		gameState.deserialize(tableText_);
	}

	void LeaderBoard::sortTable(GameState& gameState) {
		float space = buttonSize_;

		auto cmp = [](std::pair<std::string, int> const& a, std::pair<std::string, int> const& b) {
			return a.second > b.second;
			};

		std::sort(begin(tableText_), end(tableText_), cmp);

		liderBoard_.clear();
		for (const auto& player : tableText_) {
			playerName_.setString(player.first);
			playerScore_.setString(std::to_string(player.second));

			playerName_.setOrigin(sf::Vector2f(playerName_.getGlobalBounds().width / 2.f, playerName_.getGlobalBounds().height / 2.f));
			playerScore_.setOrigin(sf::Vector2f(playerScore_.getGlobalBounds().width / 2.f, playerScore_.getGlobalBounds().height / 2.f));

			playerName_.setPosition(posX_ - 60.f, posY_ + space * 1.2f);
			playerScore_.setPosition(posX_ + buttonSize_ * 4.f - 50.f, posY_ + space * 1.2f);

			liderBoard_.push_back({ playerName_ , playerScore_ });

			space += buttonSize_;
		}
	}

	// Add player in leader board
	void LeaderBoard::addPlayer(GameState& gameState) {
		tableText_.push_back({ gameState.getPlayerName() , gameState.getScore() });
	}

	// Save leader board in file
	void LeaderBoard::saveTable(GameState& gameState) {
		gameState.serialize(tableText_);
	}

	int LeaderBoard::getPositionsCount() const {
		return drawablePositions_ > liderBoard_.size() ? liderBoard_.size() : drawablePositions_;
	}

	int LeaderBoard::getShortPosCount() const {
		return shortDrawablePos_ > liderBoard_.size() ? liderBoard_.size() : shortDrawablePos_;
	}

	sf::Text LeaderBoard::getName(int num) const { return liderBoard_[num].first; }

	sf::Text LeaderBoard::getScore(int num) const { return liderBoard_[num].second; }

	sf::Text LeaderBoard::getGeneralName() const { return menuName_; }

	sf::Sprite LeaderBoard::getBackground() const { return backgroundSprite_; }

	sf::Keyboard::Key LeaderBoard::getEscapeKey() const { return escapeKey_; }

	//----------------------------------------------------------
	// FUNCTIONS
	
	// LEADER BOARD MOVEMENT

	void LeaderBoardMovement(LeaderBoard& leaderBoard, GameState& gameState, const sf::Event& event) {
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == leaderBoard.getEscapeKey()) {
				gameState.popGameState();
			}
			else if (event.key.code == sf::Keyboard::Escape) {
				gameState.popGameState();
			}
		}
	}

	//----------------------------------------------------------
	// DRAW FUNCTIONS

	void DrawLeaderBoard(LeaderBoard& leaderBoard, sf::RenderWindow& window) {
		window.draw(leaderBoard.getBackground());
		window.draw(leaderBoard.getGeneralName());
		for (int i = 0, it = leaderBoard.getPositionsCount(); i < it; ++i) {
			window.draw(leaderBoard.getName(i));
			window.draw(leaderBoard.getScore(i));
		}
	}

	void DrawGameOverLeaderBoard(LeaderBoard& leaderBoard, sf::RenderWindow& window) {
		for (int i = 0, it = leaderBoard.getShortPosCount(); i < it; ++i) {
			window.draw(leaderBoard.getName(i));
			window.draw(leaderBoard.getScore(i));
		}
	}
}