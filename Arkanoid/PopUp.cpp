#include "PopUp.h"

namespace ArkanoidGame {

	// POP UP

	PopUp::PopUp(Resources& resources, GameState& gameState, sf::RenderWindow& window) :
		resources_(resources), gameState_(gameState), window_(window) {}

	// Initialization of all pop ups buttons
	void PopUp::init(std::string popUpName, std::vector<std::string>& allButtons,
		float buttonSize, sf::Color colorOfButtons) {

		posX_ = resources_.getWindowWidth() / 2.f;
		posY_ = resources_.getWindowHeight() / 2.f;
		mainButtonColor_ = colorOfButtons;
		buttonSize_ = buttonSize;

		// Initialization of name of a pop up
		popUpName_.setFont(resources_.font);
		popUpName_.setCharacterSize(buttonSize_);
		popUpName_.setFillColor(mainButtonColor_);
		popUpName_.setString(popUpName);
		popUpName_.setOrigin(sf::Vector2f(popUpName_.getGlobalBounds().width / 2.f, popUpName_.getGlobalBounds().height / 2.f));
		popUpName_.setPosition(posX_, posY_ - buttonSize_);

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

		// Color of the first button
		int selectedButton_ = 0;
		buttons_[selectedButton_].setFillColor(chosenButtonColor_);
	}

	// Reset menu to default
	void PopUp::reset() {
		// Set choosen button to first button
		buttons_[selectedButton_].setFillColor(mainButtonColor_);
		selectedButton_ = 0;
		buttons_[selectedButton_].setFillColor(chosenButtonColor_);
	}

	// Draw pop up
	void PopUp::draw() {
		window_.draw(popUpName_);
		for (auto& i : buttons_) {
			window_.draw(i);
		}
	}

	//----------------------------------------------------------
	// PRIVATE WORK TOOLS

	void PopUp::moveUp() {
		if (selectedButton_ >= 0) {
			buttons_[selectedButton_].setFillColor(mainButtonColor_);
			--selectedButton_;

			if (selectedButton_ < 0) {
				selectedButton_ = buttons_.size() - 1;
			}
			buttons_[selectedButton_].setFillColor(chosenButtonColor_);

			// play sound of menu buttons change
			MenuMovementSound(resources_);
		}
	}

	void PopUp::moveDown() {
		size_t end = buttons_.size();

		if (selectedButton_ <= end) {
			buttons_[selectedButton_].setFillColor(mainButtonColor_);
			++selectedButton_;

			if (selectedButton_ == end) {
				selectedButton_ = 0;
			}
			buttons_[selectedButton_].setFillColor(chosenButtonColor_);

			// play sound of menu buttons change
			MenuMovementSound(resources_);
		}
	}

	//----------------------------------------------------------
	// POP UP OF CHOOSE PLAYER'S NAME
	ChooseNamePopUp::ChooseNamePopUp(Resources& resources, GameState& gameState, sf::RenderWindow& window, LeaderBoard& leaderBoard) :
		PopUp(resources, gameState, window), leaderBoard_(leaderBoard) {}

	// Initialization of all pop ups buttons
	void ChooseNamePopUp::init(std::string popUpName, std::vector<std::string>& allButtons,
		float buttonSize, sf::Color colorOfButtons) {

		posX_ = resources_.getWindowWidth() / 2.f;
		posY_ = resources_.getWindowHeight() / 2.f;
		mainButtonColor_ = colorOfButtons;
		buttonSize_ = buttonSize;

		// Initialization of name of a pop up
		popUpName_.setFont(resources_.font);
		popUpName_.setCharacterSize(buttonSize_);
		popUpName_.setFillColor(mainButtonColor_);
		popUpName_.setString(popUpName);
		popUpName_.setOrigin(sf::Vector2f(popUpName_.getGlobalBounds().width / 2.f, popUpName_.getGlobalBounds().height / 2.f));
		popUpName_.setPosition(posX_, posY_ - buttonSize_);

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
	void ChooseNamePopUp::reset() {
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

	void ChooseNamePopUp::update(const sf::Event& event) {
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::BackSpace) {
				deleteName();
			}
			else if (event.key.code == escapeKey_) {
				gameState_.pushGameState(GameStateType::GameOver);
				SoundOfChoose(resources_);
			}
			else if (event.key.code == enterKey_) {
				leaderBoard_.addPlayer();
				leaderBoard_.sortTable();
				leaderBoard_.saveTable();
				SoundOfChoose(resources_);
				gameState_.pushGameState(GameStateType::GameOver);
			}
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == enterKey_) {
				savePlayerInTable();
			}
		}
		else if (event.type == sf::Event::TextEntered) {
			enterName(event.text.unicode);
		}
	}

	void ChooseNamePopUp::draw() {
		window_.draw(popUpName_);
		window_.draw(playerName_);
		for (auto& i : buttons_) {
			window_.draw(i);
		}
	}

	//----------------------------------------------------------
	// PRIVATE WORK TOOLS
	
	// Enter player's name after game
	void ChooseNamePopUp::enterName(sf::String letter) {
		playerInput_ += letter;

		playerName_.setString(playerInput_);
		playerName_.setOrigin(sf::Vector2f(playerName_.getGlobalBounds().width / 2.f, playerName_.getGlobalBounds().height / 2.5f));
		playerName_.setPosition(posX_, posY_);
	}

	// Delete name
	void ChooseNamePopUp::deleteName() {
		playerInput_.clear();
	}

	void ChooseNamePopUp::savePlayerInTable() {
		gameState_.setPlayerName(playerName_.getString());
	}

	//----------------------------------------------------------
	// GAME OVER POP UP

	GameOverPopUp::GameOverPopUp(Resources& resources, GameState& gameState, sf::RenderWindow& window) :
		PopUp(resources, gameState, window) {}

	void GameOverPopUp::update(const sf::Event& event) {
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == upKey_) {
				moveUp();
			}
			else if (event.key.code == downKey_) {
				moveDown();
			}
			else if (event.key.code == enterKey_) {
				if (selectedButton_ == 0) {
					gameState_.pushGameState(GameStateType::GameOver);
					SoundOfChoose(resources_);
				}
				else if (selectedButton_ == 1) {
					gameState_.pushGameState(GameStateType::ChooseNameOfPlayer);
					SoundOfChoose(resources_);
				}
			}
			else if (event.key.code == escapeKey_) {
				gameState_.pushGameState(GameStateType::GameOver);
				SoundOfChoose(resources_);
			}
		}
	}

	//----------------------------------------------------------
	// GAME WIN POP UP

	GameWinPopUp::GameWinPopUp(Resources& resources, GameState& gameState, sf::RenderWindow& window) :
		PopUp(resources, gameState, window) {}


	void GameWinPopUp::update(const sf::Event& event) {
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == upKey_) {
				moveUp();
			}
			else if (event.key.code == downKey_) {
				moveDown();
			}
			else if (event.key.code == enterKey_) {
				if (selectedButton_ == 0) {
					gameState_.pushGameState(GameStateType::GameOver);
					SoundOfChoose(resources_);
				}
				else if (selectedButton_ == 1) {
					gameState_.pushGameState(GameStateType::ChooseNameOfPlayer);
					SoundOfChoose(resources_);
				}
			}
			else if (event.key.code == escapeKey_) {
				gameState_.pushGameState(GameStateType::GameOver);
				SoundOfChoose(resources_);
			}
		}
	}
}