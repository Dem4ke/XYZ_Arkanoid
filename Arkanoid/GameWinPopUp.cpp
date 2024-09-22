#include "GameWinPopUp.h"

namespace ArkanoidGame {
	GameWinPopUp::GameWinPopUp(Resources& resources, GameState& gameState, sf::RenderWindow& window)
		: resources_(resources), gameState_(gameState), window_(window) {

		init();
	}

	GameWinPopUp::~GameWinPopUp() {}

	// Initialization of all menu buttons
	void GameWinPopUp::init() {
		std::vector<std::string> mainButtons = { "No", "Yes" };

		float posX = resources_.getWindowWidth() / 2.f;
		float posY = resources_.getWindowHeight() / 3.f;

		// Initialization of a background of the menu
		backgroundSprite_.setTexture(resources_.mainMenuBackground);
		SetSize(backgroundSprite_, resources_.getWindowWidth(), resources_.getWindowHeight());

		// Initialization of a name of the menu
		menuName_.setFont(resources_.font);
		menuName_.setCharacterSize(menuNameTextSize_);
		menuName_.setFillColor(mainButtonColor_);
		menuName_.setString("Congratulations! You crashed them all/nDo you want to save your score?");
		menuName_.setOrigin(sf::Vector2f(menuName_.getGlobalBounds().width / 2.f, menuName_.getGlobalBounds().height / 2.f));
		menuName_.setPosition(posX, posY - menuNameTextSize_);

		// Initialization of menu's buttons
		sf::Text menuButtons_;
		float space = menuButtonsTextSize_;
		menuButtons_.setFont(resources_.font);
		menuButtons_.setCharacterSize(menuButtonsTextSize_);
		menuButtons_.setFillColor(mainButtonColor_);

		buttons_.clear();
		for (auto& i : mainButtons) {
			menuButtons_.setString(i);
			menuButtons_.setOrigin(sf::Vector2f(menuButtons_.getGlobalBounds().width / 2.f, menuButtons_.getGlobalBounds().height / 2.f));
			menuButtons_.setPosition(posX, posY + space * 1.2f);
			buttons_.push_back(menuButtons_);
			space += menuButtonsTextSize_;
		}

		// Color of the first button
		int selectedButton_ = 0;
		buttons_[selectedButton_].setFillColor(chosenButtonColor_);
	}

	// Reset menu to default
	void GameWinPopUp::reset() {
		// Set choosen button to first button
		buttons_[selectedButton_].setFillColor(mainButtonColor_);
		selectedButton_ = 0;
		buttons_[selectedButton_].setFillColor(chosenButtonColor_);
	}

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

	void GameWinPopUp::draw() {
		window_.draw(backgroundSprite_);
		window_.draw(menuName_);
		for (auto& i : buttons_) {
			window_.draw(i);
		}
	}

	//----------------------------------------------------------
	// PRIVATE WORK TOOLS

	void GameWinPopUp::moveUp() {
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

	void GameWinPopUp::moveDown() {
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
}