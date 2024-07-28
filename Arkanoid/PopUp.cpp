#include "PopUp.h"

namespace SnakeGame {

	// POP UP

	PopUp::PopUp(Resources& resources) : Menu(resources) {}

	void PopUp::init(std::string popUpName, std::vector<std::string>& allButtons,
		float buttonSize, sf::Color colorOfButtons) {

		posX_ = resources_.getWindowWidth() / 2.f;
		posY_ = resources_.getWindowHeight() / 2.f;
		mainButtonColor_ = colorOfButtons;
		buttonSize_ = buttonSize;

		// Initialization of name of a pop up
		menuName_.setFont(resources_.font);
		menuName_.setCharacterSize(buttonSize_);
		menuName_.setFillColor(mainButtonColor_);
		menuName_.setString(popUpName);
		menuName_.setOrigin(sf::Vector2f(menuName_.getGlobalBounds().width / 2.f, menuName_.getGlobalBounds().height / 2.f));
		menuName_.setPosition(posX_, posY_ - buttonSize_);

		// Initialization of pop up's buttons
		sf::Text menuButtons_;
		float space = buttonSize_;
		menuButtons_.setFont(resources_.font);
		menuButtons_.setCharacterSize(buttonSize_);
		menuButtons_.setFillColor(mainButtonColor_);

		buttons_.clear();
		for (auto& i : allButtons) {
			menuButtons_.setString(i);
			menuButtons_.setOrigin(sf::Vector2f(menuButtons_.getGlobalBounds().width / 2.f, menuButtons_.getGlobalBounds().height / 2.f));
			menuButtons_.setPosition(posX_, posY_ + space * 1.2f);
			buttons_.push_back(menuButtons_);
			space += buttonSize_;
		}

		// Init player's name text characteristics 
		playerName_.setFont(resources_.font);
		playerName_.setCharacterSize(buttonSize_);
		playerName_.setFillColor(mainButtonColor_);
		playerName_.setString(DefaultPlayerName_);
		playerName_.setOrigin(sf::Vector2f(playerName_.getGlobalBounds().width / 2.f, playerName_.getGlobalBounds().height / 2.5f));
		playerName_.setPosition(posX_, posY_);

		// Color of the first button
		int selectedButton_ = 0;
		buttons_[selectedButton_].setFillColor(chosenButtonColor_);
	}

	// Reset pop up to default
	void PopUp::reset() {
		// Set choosen button to first button
		buttons_[selectedButton_].setFillColor(mainButtonColor_);
		selectedButton_ = 0;
		buttons_[selectedButton_].setFillColor(chosenButtonColor_);

		// Delete entered name of player and set a default
		deleteName();
		playerName_.setString(DefaultPlayerName_);
		playerName_.setOrigin(sf::Vector2f(playerName_.getGlobalBounds().width / 2.f, playerName_.getGlobalBounds().height / 2.5f));
		playerName_.setPosition(posX_, posY_);
	}

	// Enter player's name after game
	void PopUp::enterName(sf::String letter) {
		playerInput_ += letter;

		playerName_.setString(playerInput_);
		playerName_.setOrigin(sf::Vector2f(playerName_.getGlobalBounds().width / 2.f, playerName_.getGlobalBounds().height / 2.5f));
		playerName_.setPosition(posX_, posY_);
	}

	// Delete name
	void PopUp::deleteName() {
		playerInput_.clear();
	}

	void PopUp::savePlayerInTable(GameState& gameState) {
		gameState.setPlayerName(playerName_.getString());
	}

	sf::Text PopUp::getPlayerName() { return playerName_; }

	int PopUp::getPositionsCount() const { return drawablePositions_; }

	//----------------------------------------------------------
	// FUNCTIONS
	
	// POP UP MOVEMENT

	void GameOverPopUpMovement(PopUp& popUp, GameState& gameState, const sf::Event& event) {
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == popUp.getUpKey()) {
				popUp.moveUp();
			}
			else if (event.key.code == popUp.getDownKey()) {
				popUp.moveDown();
			}
			else if (event.key.code == popUp.getEnterKey()) {
				if (popUp.getSelectedButton() == 0) {
					popUp.chooseButtonSound();
					gameState.pushGameState(GameStateType::GameOver);
				}
				else if (popUp.getSelectedButton() == 1) {
					popUp.chooseButtonSound();
					gameState.pushGameState(GameStateType::ChooseNameOfPlayer);
				}
			}
			else if (event.key.code == popUp.getEscapeKey()) {
				popUp.chooseButtonSound();
				gameState.pushGameState(GameStateType::GameOver);
			}
		}
	}

	void ChooseNamePopUpMovement(PopUp& popUp, GameState& gameState, LeaderBoard& leaderBoard, const sf::Event& event) {
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::BackSpace) {
				popUp.deleteName();
			}
			else if (event.key.code == popUp.getEscapeKey()) {
				popUp.chooseButtonSound();
				gameState.pushGameState(GameStateType::GameOver);
			}
			else if (event.key.code == popUp.getEnterKey()) {
				leaderBoard.addPlayer(gameState);
				leaderBoard.sortTable(gameState);
				leaderBoard.saveTable(gameState);
				popUp.chooseButtonSound();
				gameState.pushGameState(GameStateType::GameOver);
			}
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == popUp.getEnterKey()) {
				popUp.savePlayerInTable(gameState);
			}
		}
		else if (event.type == sf::Event::TextEntered) {
			popUp.enterName(event.text.unicode);
		}
	}

	//----------------------------------------------------------
	// DRAW FUNCTIONS

	void DrawPopUp(PopUp& popUp, sf::RenderWindow& window, GameState& gameState) {
		window.draw(popUp.getGeneralName());
		for (int i = 0, it = popUp.getButtonsCount(); i < it; ++i) {
			window.draw(popUp.getButton(i));
		}

		if (gameState.getCurrentGameState() == GameStateType::ChooseNameOfPlayer) {
			window.draw(popUp.getPlayerName());
		}
	}
}