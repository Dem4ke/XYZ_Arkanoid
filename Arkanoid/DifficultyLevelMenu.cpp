#include "DifficultyLevelMenu.h"

namespace ArkanoidGame {
	DifficultyLevelMenu::DifficultyLevelMenu(Resources& resources, GameState& gameState, sf::RenderWindow& window)
		: resources_(resources), gameState_(gameState), window_(window) {

		init();
	}

	DifficultyLevelMenu::~DifficultyLevelMenu() {}

	// Initialization of all menu buttons
	void DifficultyLevelMenu::init() {
		std::vector<std::string> mainButtons = { "Easy", "Medium", "Hard" };

		float posX = resources_.getWindowWidth() / 2.f;
		float posY = resources_.getWindowHeight() / 3.f;

		// Initialization of background of menu
		backgroundSprite_.setTexture(resources_.mainMenuBackground);
		SetSize(backgroundSprite_, resources_.getWindowWidth(), resources_.getWindowHeight());

		// Initialization of name of a game
		menuName_.setFont(resources_.font);
		menuName_.setCharacterSize(menuNameTextSize_);
		menuName_.setFillColor(mainButtonColor_);
		menuName_.setString("Difficulity level");
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
	void DifficultyLevelMenu::reset() {
		// Set choosen button to first button
		buttons_[selectedButton_].setFillColor(mainButtonColor_);
		selectedButton_ = 0;
		buttons_[selectedButton_].setFillColor(chosenButtonColor_);
	}

	void DifficultyLevelMenu::update(const sf::Event& event) {
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == upKey_) {
				moveUp();
			}
			else if (event.key.code == downKey_) {
				moveDown();
			}
			else if (event.key.code == escapeKey_) {
				SoundOfChoose(resources_);
				gameState_.popGameState();
			}
			else if (event.key.code == enterKey_) {
				if (selectedButton_ == 0) {
					gameState_.setNewDifficulty(DifficultyLevel::Easy);
					gameState_.pushGameState(GameStateType::GameReset);
					SoundOfChoose(resources_);
				}
				else if (selectedButton_ == 1) {
					gameState_.setNewDifficulty(DifficultyLevel::Medium);
					gameState_.pushGameState(GameStateType::GameReset);
					SoundOfChoose(resources_);
				}
				else if (selectedButton_ == 2) {
					gameState_.setNewDifficulty(DifficultyLevel::Hard);
					gameState_.pushGameState(GameStateType::GameReset);
					SoundOfChoose(resources_);
				}
			}
		}
	}

	void DifficultyLevelMenu::draw() {
		window_.draw(backgroundSprite_);
		window_.draw(menuName_);
		for (auto& i : buttons_) {
			window_.draw(i);
		}
	}

	//----------------------------------------------------------
	// PRIVATE WORK TOOLS

	void DifficultyLevelMenu::moveUp() {
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

	void DifficultyLevelMenu::moveDown() {
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