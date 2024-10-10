#include "ChooseNamePopUp.h"

namespace ArkanoidGame {
	ChooseNamePopUp::ChooseNamePopUp(Resources& resources, GameState& gameState, sf::RenderWindow& window, std::shared_ptr<LeaderBoard> leaderBoard)
		: resources_(resources), gameState_(gameState), window_(window), leaderBoard_(leaderBoard) {
	
		init();
	}

	// Initialization of all pop ups buttons
	void ChooseNamePopUp::init() {
		std::vector<std::string> mainButtons = { "Enter" };

		posX_ = resources_.getWindowWidth() / 2.f;
		posY_ = resources_.getWindowHeight() / 2.f;

		// Initialization of name of a pop up
		menuName_.setFont(resources_.font);
		menuName_.setCharacterSize(menuNameTextSize_);
		menuName_.setFillColor(mainButtonColor_);
		menuName_.setString("Enter your name");
		menuName_.setOrigin(sf::Vector2f(menuName_.getGlobalBounds().width / 2.f, menuName_.getGlobalBounds().height / 2.f));
		menuName_.setPosition(posX_, posY_ - menuNameTextSize_);

		// Initialization of pop up's buttons
		sf::Text menuButtons_;
		float space = static_cast<float> (menuButtonsTextSize_);
		menuButtons_.setFont(resources_.font);
		menuButtons_.setCharacterSize(menuButtonsTextSize_);
		menuButtons_.setFillColor(mainButtonColor_);

		buttons_.clear();
		for (auto& i : mainButtons) {
			menuButtons_.setString(i);
			menuButtons_.setOrigin(sf::Vector2f(menuButtons_.getGlobalBounds().width / 2.f, menuButtons_.getGlobalBounds().height / 2.f));
			menuButtons_.setPosition(posX_, posY_ + space * 1.2f);
			buttons_.push_back(menuButtons_);
			space += menuButtonsTextSize_;
		}

		// Init player's name text characteristics 
		playerName_.setFont(resources_.font);
		playerName_.setCharacterSize(menuButtonsTextSize_);
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
				leaderBoard_->addPlayer();
				leaderBoard_->sortTable();
				leaderBoard_->saveTable();
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

	// Draw pop up
	void ChooseNamePopUp::draw() {
		window_.draw(menuName_);
		window_.draw(playerName_);
		for (auto& i : buttons_) {
			window_.draw(i);
		}
	}

	// Return game state which describes this menu
	GameStateType ChooseNamePopUp::getState() {
		return GameStateType::ChooseNameOfPlayer;
	}

	//----------------------------------------------------------
	// PRIVATE WORK TOOLS

	void ChooseNamePopUp::moveUp() {
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

	void ChooseNamePopUp::moveDown() {
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
}