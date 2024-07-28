#include "Menu.h"

namespace SnakeGame {

	// MAIN MENU

	Menu::Menu(Resources& resources, GameState& gameState, sf::RenderWindow& window) :
		resources_(resources), gameState_(gameState), window_(window) {}

	// Initialization of all menu buttons
	void Menu::init(std::string menuName, std::vector<std::string>& allButtons,
		float buttonSize, sf::Color colorOfButtons) {

		float posX = resources_.getWindowWidth() / 2.f;
		float posY = resources_.getWindowHeight() / 3.f;
		mainButtonColor_ = colorOfButtons;

		// Initialization of background of menu
		backgroundSprite_.setTexture(resources_.mainMenuBackground);
		SetSpriteSize(backgroundSprite_, resources_.getWindowWidth(), resources_.getWindowHeight());

		// Initialization of name of a game
		menuName_.setFont(resources_.font);
		menuName_.setCharacterSize(buttonSize * 1.5f);
		menuName_.setFillColor(mainButtonColor_);
		menuName_.setString(menuName);
		menuName_.setOrigin(sf::Vector2f(menuName_.getGlobalBounds().width / 2.f, menuName_.getGlobalBounds().height / 2.f));
		menuName_.setPosition(posX, posY - buttonSize);

		// Initialization of menu's buttons
		sf::Text menuButtons_;
		float space = buttonSize;
		menuButtons_.setFont(resources_.font);
		menuButtons_.setCharacterSize(buttonSize);
		menuButtons_.setFillColor(mainButtonColor_);

		buttons_.clear();
		for (auto& i : allButtons) {
			menuButtons_.setString(i);
			menuButtons_.setOrigin(sf::Vector2f(menuButtons_.getGlobalBounds().width / 2.f, menuButtons_.getGlobalBounds().height / 2.f));
			menuButtons_.setPosition(posX, posY + space * 1.2f);
			buttons_.push_back(menuButtons_);
			space += buttonSize;
		}

		// Color of the first button
		int selectedButton_ = 0;
		buttons_[selectedButton_].setFillColor(chosenButtonColor_);
	}

	// Reset menu to default
	void Menu::reset() {
		// Set choosen button to first button
		buttons_[selectedButton_].setFillColor(mainButtonColor_);
		selectedButton_ = 0;
		buttons_[selectedButton_].setFillColor(chosenButtonColor_);
	}

	void Menu::update(const sf::Event& event) {
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == upKey_) {
				moveUp();
			}
			else if (event.key.code == downKey_) {
				moveDown();
			}
			else if (event.key.code == escapeKey_) {
				gameState_.pushGameState(GameStateType::ExitDialog);
				SoundOfChoose(resources_);
			}
			else if (event.key.code == enterKey_) {
				if (selectedButton_ == 0) {
					gameState_.pushGameState(GameStateType::Game);
					SoundOfChoose(resources_);
				}
				else if (selectedButton_ == 1) {
					gameState_.pushGameState(GameStateType::DifficulityLevelChoose);
					SoundOfChoose(resources_);
				}
				else if (selectedButton_ == 2) {
					gameState_.pushGameState(GameStateType::LeaderBoard);
					SoundOfChoose(resources_);
				}
				else if (selectedButton_ == 3) {
					gameState_.pushGameState(GameStateType::Options);
					SoundOfChoose(resources_);
				}
				else if (selectedButton_ == 4) {
					gameState_.pushGameState(GameStateType::ExitDialog);
					SoundOfChoose(resources_);
				}
			}
		}
	}

	void Menu::draw() {
		window_.draw(backgroundSprite_);
		window_.draw(menuName_);
		for (auto& i : buttons_) {
			window_.draw(i);
		}
	}

	//----------------------------------------------------------
	// PRIVATE WORK TOOLS

	void Menu::moveUp() {
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

	void Menu::moveDown() {
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
	// OPTIONS MENU
	OptionsMenu::OptionsMenu(Resources& resources, GameState& gameState, sf::RenderWindow& window) :
		Menu(resources, gameState, window) {}

	void OptionsMenu::update(const sf::Event& event) {
		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == upKey_) {
				moveUp();
			}
			else if (event.key.code == downKey_) {
				moveDown();
			}
			else if (event.key.code == escapeKey_) {
				gameState_.popGameState();
				SoundOfChoose(resources_);
			}
			else if (event.key.code == enterKey_) {
				if (selectedButton_ == 0) {
					if (buttons_[0].getString() == "Music: On") {
						changeButton(0, "Music: Off");
						SoundOfChoose(resources_);
						StopBackMusic(resources_);
					}
					else if (buttons_[0].getString() == "Music: Off") {
						changeButton(0, "Music: On");
						SoundOfChoose(resources_);
						PlayBackMusic(resources_);
					}
				}
				else if (selectedButton_ == 1) {
					if (buttons_[1].getString() == "Sounds: On") {
						changeButton(1, "Sounds: Off");
						SoundOfChoose(resources_);
						SetSoundsVolume(resources_, 0.f);
					}
					else if (buttons_[1].getString() == "Sounds: Off") {
						changeButton(1, "Sounds: On");
						SoundOfChoose(resources_);
						SetSoundsVolume(resources_, 5.f);
					}
				}
				else if (selectedButton_ == 2) {
					gameState_.pushGameState(GameStateType::WindowSizeEdit);
				}
			}
		}
	}

	// Change string to button from inputed index
	void OptionsMenu::changeButton(int index, std::string newButton) { 
		buttons_[index].setString(newButton); 
	}

	//----------------------------------------------------------
	// MENU OF CHOICE DIFFICULTY OF LEVELS
	DifficultyLevelMenu::DifficultyLevelMenu(Resources& resources, GameState& gameState, sf::RenderWindow& window) :
		Menu(resources, gameState, window) {}

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
					gameState_.setNewDifficulty(DifficultyLevel::HarderThanEasy);
					gameState_.pushGameState(GameStateType::GameReset);
					SoundOfChoose(resources_);
				}
				else if (selectedButton_ == 2) {
					gameState_.setNewDifficulty(DifficultyLevel::Medium);
					gameState_.pushGameState(GameStateType::GameReset);
					SoundOfChoose(resources_);
				}
				else if (selectedButton_ == 3) {
					gameState_.setNewDifficulty(DifficultyLevel::LessThanHard);
					gameState_.pushGameState(GameStateType::GameReset);
					SoundOfChoose(resources_);
				}
				else if (selectedButton_ == 4) {
					gameState_.setNewDifficulty(DifficultyLevel::Hard);
					gameState_.pushGameState(GameStateType::GameReset);
					SoundOfChoose(resources_);
				}
			}
		}
	}

	//----------------------------------------------------------
	// FUNCTIONS
	
	// MENU MOVEMENT

//	void WindowEditMenuMovement(Menu& windowEditMenu, GameState& gameState, const sf::Event& event, sf::RenderWindow& window) {
//		if (event.type == sf::Event::KeyReleased) {
//			if (event.key.code == windowEditMenu.getUpKey()) {
//				windowEditMenu.moveUp();
//			}
//			else if (event.key.code == windowEditMenu.getDownKey()) {
//				windowEditMenu.moveDown();
//			}
//			else if (event.key.code == windowEditMenu.getEscapeKey()) {
//				windowEditMenu.chooseButtonSound();
//				gameState.popGameState();
//			}
//			else if (event.key.code == windowEditMenu.getEnterKey()) {
//				if (windowEditMenu.getSelectedButton() == 0) {
//					windowEditMenu.chooseButtonSound();
//					window.setSize(sf::Vector2u(800, 600));
//				}
//				else if (windowEditMenu.getSelectedButton() == 1) {
//					windowEditMenu.chooseButtonSound();
//					window.setSize(sf::Vector2u(1920, 1080));
//				}
//				else if (windowEditMenu.getSelectedButton() == 2) {
//					windowEditMenu.chooseButtonSound();
//					window.setSize(sf::Vector2u(1280, 720));
//				}
//			}
//		}
//	}
//
//	void ExitMenuMovement(Menu& exitMenu, GameState& gameState, const sf::Event& event, sf::RenderWindow& window) {
//		if (event.type == sf::Event::KeyReleased) {
//			if (event.key.code == exitMenu.getUpKey()) {
//				exitMenu.moveUp();
//			}
//			else if (event.key.code == exitMenu.getDownKey()) {
//				exitMenu.moveDown();
//			}
//			else if (event.key.code == exitMenu.getEscapeKey()) {
//				exitMenu.chooseButtonSound();
//				gameState.popGameState();
//			}
//			else if (event.key.code == exitMenu.getEnterKey()) {
//				if (exitMenu.getSelectedButton() == 0) {
//					exitMenu.chooseButtonSound();
//					window.close();
//					return;
//				}
//				else if (exitMenu.getSelectedButton() == 1) {
//					exitMenu.chooseButtonSound();
//					gameState.popGameState();
//				}
//			}
//		}
//	}
//
//	void PauseMenuMovement(Menu& pauseMenu, GameState& gameState, const sf::Event& event) {
//		if (event.type == sf::Event::KeyReleased) {
//			if (event.key.code == pauseMenu.getUpKey()) {
//				pauseMenu.moveUp();
//			}
//			else if (event.key.code == pauseMenu.getDownKey()) {
//				pauseMenu.moveDown();
//			}
//			else if (event.key.code == pauseMenu.getEscapeKey()) {
//				pauseMenu.chooseButtonSound();
//				gameState.popGameState();
//				sf::sleep(sf::seconds(1));
//			}
//			else if (event.key.code == pauseMenu.getEnterKey()) {
//				if (pauseMenu.getSelectedButton() == 0) {
//					gameState.pushGameState(GameStateType::GameReset);
//					pauseMenu.chooseButtonSound();
//				}
//				else if (pauseMenu.getSelectedButton() == 1) {
//					pauseMenu.chooseButtonSound();
//					gameState.popGameState();
//					sf::sleep(sf::seconds(1));
//				}
//			}
//		}
//	}
//
//	void GameOverMenuMovement(Menu& gameOverMenu, GameState& gameState, const sf::Event& event) {
//		if (event.type == sf::Event::KeyReleased) {
//			if (event.key.code == gameOverMenu.getUpKey()) {
//				gameOverMenu.moveUp();
//			}
//			else if (event.key.code == gameOverMenu.getDownKey()) {
//				gameOverMenu.moveDown();
//			}
//			else if (event.key.code == gameOverMenu.getEnterKey()) {
//				if (gameOverMenu.getSelectedButton() == 0) {
//					gameOverMenu.chooseButtonSound();
//					gameState.pushGameState(GameStateType::PlayAgain);
//				}
//				else if (gameOverMenu.getSelectedButton() == 1) {
//					gameOverMenu.chooseButtonSound();
//					gameState.pushGameState(GameStateType::GameReset);
//				}
//			}
//			else if (event.key.code == gameOverMenu.getEscapeKey()) {
//				gameOverMenu.chooseButtonSound();
//				gameState.pushGameState(GameStateType::GameReset);
//			}
//		}
//	}
//
	//----------------------------------------------------------
	// TOOLBOX FUNCTIONS

	void ExitInPauseMenu(GameState& gameState) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) 
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {

			gameState.pushGameState(GameStateType::Pause);
		}
	}
//
//	//----------------------------------------------------------
//	// DRAW FUNCTIONS
//
//	void DrawMenu(Menu& menu, sf::RenderWindow& window) {
//		window.draw(menu.getBackground());
//		window.draw(menu.getGeneralName());
//		for (int i = 0, it = menu.getButtonsCount(); i < it; ++i) {
//			window.draw(menu.getButton(i));
//		}
//	}
//}