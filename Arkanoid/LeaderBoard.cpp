#include "LeaderBoard.h"

namespace ArkanoidGame {
	LeaderBoard::LeaderBoard(Resources& resources, GameState& gameState, sf::RenderWindow& window) :
		resources_(resources), gameState_(gameState), window_(window) {

		init();
	}

	LeaderBoard::~LeaderBoard() {}

	void LeaderBoard::init() {
		posX_ = resources_.getWindowWidth() / 2.f;
		posY_ = resources_.getWindowHeight() / 5.f;

		// Initialization of a menu name
		menuName_.setFont(resources_.font);
		menuName_.setCharacterSize(menuNameTextSize_);
		menuName_.setFillColor(mainButtonColor_);
		menuName_.setString("Leader board");
		menuName_.setOrigin(sf::Vector2f(menuName_.getGlobalBounds().width / 2.f, menuName_.getGlobalBounds().height / 2.f));
		menuName_.setPosition(posX_, posY_ - menuNameTextSize_);

		// Initialization of players' names
		playerName_.setFont(resources_.font);
		playerName_.setCharacterSize(menuButtonsTextSize_);
		playerName_.setFillColor(mainButtonColor_);

		// Initialization of players' score
		playerScore_.setFont(resources_.font);
		playerScore_.setCharacterSize(menuButtonsTextSize_);
		playerScore_.setFillColor(mainButtonColor_);

		backgroundSprite_.setTexture(resources_.mainMenuBackground);

		SetSize(backgroundSprite_, resources_.getWindowWidth(), resources_.getWindowHeight());

		// Get leader board from file
		gameState_.deserialize(tableText_);
		sortTable();
	}

	// Reset menu to default
	void LeaderBoard::reset() {}

	void LeaderBoard::update(const sf::Event& event) {
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == escapeKey_ || event.key.code == sf::Keyboard::Escape) {
				gameState_.popGameState();
			}
		}
	}

	void LeaderBoard::sortTable() {
		float space = static_cast<float> (menuButtonsTextSize_);

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
			playerScore_.setPosition(posX_ + menuButtonsTextSize_ * 4.f - 50.f, posY_ + space * 1.2f);

			liderBoard_.push_back({ playerName_ , playerScore_ });

			space += menuButtonsTextSize_;
		}
	}

	// Add player in leader board
	void LeaderBoard::addPlayer() {
		tableText_.push_back({ gameState_.getPlayerName() , gameState_.getScore() });
	}

	// Save leader board in file
	void LeaderBoard::saveTable() {
		gameState_.serialize(tableText_);
	}

	// Draw leader board in menu
	void LeaderBoard::draw() {
		int it = drawablePositions_ > liderBoard_.size() ? liderBoard_.size() : drawablePositions_;

		window_.draw(backgroundSprite_);
		window_.draw(menuName_);
		for (int i = 0; i < it; ++i) {
			window_.draw(liderBoard_[i].first);
			window_.draw(liderBoard_[i].second);
		}
	}

	// Return game state which describes this menu
	GameStateType LeaderBoard::getState() {
		return GameStateType::LeaderBoard;
	}

	//-----------------------------------------------------------------------------------
	// SHORT LEADER BOARD

	ShortLeaderBoard::ShortLeaderBoard(Resources& resources, GameState& gameState, sf::RenderWindow& window) 
		: LeaderBoard(resources, gameState, window) {

		init();
	}

	ShortLeaderBoard::~ShortLeaderBoard() {}

	void ShortLeaderBoard::init() {
		posX_ = resources_.getWindowWidth() / 2.f;
		posY_ = resources_.getWindowHeight() / 3.3f;

		// Initialization of players' names
		playerName_.setFont(resources_.font);
		playerName_.setCharacterSize(menuButtonsTextSize_);
		playerName_.setFillColor(mainButtonColor_);

		// Initialization of players' score
		playerScore_.setFont(resources_.font);
		playerScore_.setCharacterSize(menuButtonsTextSize_);
		playerScore_.setFillColor(mainButtonColor_);

		backgroundSprite_.setTexture(resources_.mainMenuBackground);

		SetSize(backgroundSprite_, resources_.getWindowWidth(), resources_.getWindowHeight());

		// Get leader board from file
		gameState_.deserialize(tableText_);
		sortTable();
	}

	// Draw leader board after game over in short pop up
	void ShortLeaderBoard::draw() {
		int it = drawablePositions_ > liderBoard_.size() ? liderBoard_.size() : drawablePositions_;

		for (int i = 0; i < it; ++i) {
			window_.draw(liderBoard_[i].first);
			window_.draw(liderBoard_[i].second);
		}
	}

	// Return game state which describes this menu
	GameStateType ShortLeaderBoard::getState() {
		return GameStateType::GameOver;
	}
}