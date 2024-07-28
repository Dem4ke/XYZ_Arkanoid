#include "Game.h"

namespace SnakeGame {

	Game::Game(Resources& resources, sf::RenderWindow& window) : 
		resources_(resources), window_(window),
		mainMenu_(resources, gameState_, window), 
		difficultyLevelMenu_(resources, gameState_, window),
		optionsMenu_(resources, gameState_, window), 
		exitMenu_(resources, gameState_, window),
		pauseMenu_(resources, gameState_, window), 
		gameOverMenu_(resources, gameState_, window),
		leaderBoard_(resources), windowEditMenu_(resources),
		UI_(resources), gameField_(resources, gameState_), 
		gameOverPopUp_(resources), chooseName_(resources) {}

	void Game::initGame() {
		std::vector<std::string> mainButtons = { "Play game", "Difficulity level", "Leader board", "Options", "Exit" };
		std::vector<std::string> dufficulityLevelButtons = { "Easy", "Harder than Easy", "Medium", "Pussy hard", "Die hard" };
		std::vector<std::string> optionsButtons = { "Music: On", "Sounds: On", 
				"Window size " + std::to_string(window_.getSize().y) + "x" + std::to_string(window_.getSize().x) };
		std::vector<std::string> windowEditButtons = { "800 x 600", "1280 x 720", "1920 x 1080"};
		std::vector<std::string> exitButtons = { "Yes", "No" };
		std::vector<std::string> pauseButtons = { "Yes", "No" };
		std::vector<std::string> gameOverButtons = { "\n\n\n\n\n\n\n\nPlay again", "\n\n\n\n\n\n\n\nExit"};
		std::vector<std::string> gameOverPopUpButtons = { "No", "Yes" };
		std::vector<std::string> chooseNamePopUpButtons = { "\n\nEnter" };

		// Menu initialization (Name of menu, vector of buttons, size of buttons, color of buttons (defaultd - white), id of menu (defaultd - 0)
		// Name of menu will be in 1.5 bigger, id of menu needs for choose of background
		// id: 0 - empty background, 1 or any other - main background
		mainMenu_.init("Snake Game", mainButtons, 40.f, sf::Color::White, 1);
		difficultyLevelMenu_.init("Difficulity level", dufficulityLevelButtons, 40.f, sf::Color::White, 1);
		optionsMenu_.init("Options", optionsButtons, 40.f, sf::Color::White, 1);
		windowEditMenu_.init("Edit window size", windowEditButtons, 40.f, sf::Color::White, 1);
		exitMenu_.init("Do you want to exit?", exitButtons, 40.f, sf::Color::White, 1);
		pauseMenu_.init("Do you want to exit\n\tin main menu?\n", pauseButtons, 40.f, sf::Color::White, 0);
		gameOverMenu_.init("Game Over\n\n\n", gameOverButtons, 40.f, sf::Color::White, 0);

		// Leader board initialization (Name of menu, size of names, number of drawable positions)
		leaderBoard_.init("Leader Board", 40.f, 8, gameState_);

		// Initialization of pop ups (Name of pop up, vector of buttons, size of buttons, color of buttons)
		gameOverPopUp_.init("Do you want to save your score?", gameOverPopUpButtons, 40.f);
		chooseName_.init("Enter your name", chooseNamePopUpButtons, 40.f);

		// User interface initialization (size of a text elements)
		UI_.init(20.f);
		
		// Initialization of a background music and start to play it
		SetMusicVolume(resources_, 5.f);
		PlayBackMusic(resources_);

		// Initialization of start sounds volume
		SetSoundsVolume(resources_, 5.f);

		// Initialization of background of the game
		initBackground();

		restartGame();
	}

	void Game::restartGame() {
		// Reset game state 
		gameState_.restartGameState();
		
		// Initialization of game field, and reset all game objects
		gameField_.reset();

		// Reset menus
		mainMenu_.reset();
		difficultyLevelMenu_.reset();
		optionsMenu_.reset();
		exitMenu_.reset();
		pauseMenu_.reset();
		gameOverMenu_.reset();

		// Load leader board from file and sort it
		leaderBoard_.sortTable(gameState_);

		// Reset score and player name
		gameState_.reset();
		UI_.scoreUpdate(gameState_);

		// Reset pop ups
		gameOverPopUp_.reset();
		chooseName_.reset();
	}

	// Update menu states, it works only with Event
	void Game::updateMenu(sf::Event& event) {
		switch (gameState_.getCurrentGameState()) {
		case GameStateType::MainMenu: {
			MainMenuMovement(mainMenu_, gameState_, event);
			break;
		}
		case GameStateType::DifficulityLevelChoose: {
			DiffLvlMenuMovement(difficultyLevelMenu_, gameState_, event);
			break;
		}
		case GameStateType::Options: {
			OptionsMenuMovement(optionsMenu_, gameState_, event);
			break;
		}
		case GameStateType::WindowSizeEdit: {
			WindowEditMenuMovement(windowEditMenu_, gameState_, event, window_);
		}
		case GameStateType::ExitDialog: {
			ExitMenuMovement(exitMenu_, gameState_, event, window_);
			break;
		}
		case GameStateType::Pause: {
			PauseMenuMovement(pauseMenu_, gameState_, event);
			break;
		}
		case GameStateType::LeaderBoard: {
			LeaderBoardMovement(leaderBoard_, gameState_, event);
			break;
		}
		case GameStateType::GameOver: {
			GameOverMenuMovement(gameOverMenu_, gameState_, event);
			break;
		}
		case GameStateType::GameOverPopUp: {
			GameOverPopUpMovement(gameOverPopUp_, gameState_, event);
			break;
		}
		case GameStateType::ChooseNameOfPlayer: {
			ChooseNamePopUpMovement(chooseName_, gameState_, leaderBoard_, event);
			break;
		}
		}
	}

	// Update only game process 
	void Game::updateGame(const float& deltaTime) {
		if (gameState_.getCurrentGameState() == GameStateType::Game) {

			// Update main game process
			gameField_.update(deltaTime);

			// Pause menu maker
			ExitInPauseMenu(gameState_);

			// Update player's score
			UI_.scoreUpdate(gameState_);
		}
	}

	void Game::gameOver() {
		if (gameState_.getCurrentGameState() == GameStateType::GameOver) {
			leaderBoard_.sortTable(gameState_);
		}
		else if (gameState_.getCurrentGameState() == GameStateType::PlayAgain) {
			restartGame();
			gameState_.pushGameState(GameStateType::Game);
		}
		else if (gameState_.getCurrentGameState() == GameStateType::GameReset) {
			restartGame();
		}
	}

	void Game::drawGame() {
		if (gameState_.getCurrentGameState() == GameStateType::MainMenu) {
			DrawMenu(mainMenu_, window_);
		}
		else if (gameState_.getCurrentGameState() == GameStateType::DifficulityLevelChoose) {
			DrawMenu(difficultyLevelMenu_, window_);
		}
		else if (gameState_.getCurrentGameState() == GameStateType::Options) {
			DrawMenu(optionsMenu_, window_);
		}
		else if (gameState_.getCurrentGameState() == GameStateType::WindowSizeEdit) {
			DrawMenu(windowEditMenu_, window_);
		}
		else if (gameState_.getCurrentGameState() == GameStateType::ExitDialog) {
			DrawMenu(exitMenu_, window_);
		}
		else if (gameState_.getCurrentGameState() == GameStateType::Pause) {
			window_.draw(gameBackSprite_);
			DrawGameField(gameField_, window_);
			DrawMenu(pauseMenu_, window_);
		}
		else if (gameState_.getCurrentGameState() == GameStateType::GameOver) {
			window_.draw(gameBackSprite_);
			DrawGameField(gameField_, window_);
			DrawMenu(gameOverMenu_, window_);
			DrawGameOverLeaderBoard(leaderBoard_, window_);
		}
		else if (gameState_.getCurrentGameState() == GameStateType::GameOverPopUp) {
			window_.draw(gameBackSprite_);
			DrawGameField(gameField_, window_);
			DrawPopUp(gameOverPopUp_, window_, gameState_);
			DrawGameOverUI(UI_, window_);
		}
		else if (gameState_.getCurrentGameState() == GameStateType::ChooseNameOfPlayer) {
			window_.draw(gameBackSprite_);
			DrawGameField(gameField_, window_);
			DrawPopUp(chooseName_, window_, gameState_);
			DrawGameOverUI(UI_, window_);
		}
		else if (gameState_.getCurrentGameState() == GameStateType::LeaderBoard) {
			DrawLeaderBoard(leaderBoard_, window_);
		}
		else if (gameState_.getCurrentGameState() == GameStateType::Game) {
			window_.draw(gameBackSprite_);
			DrawGameField(gameField_, window_);
			DrawUI(UI_, window_);
		}
	}

	void Game::initBackground() {
		// Initialization of background of the game
		gameBackSprite_.setTexture(resources_.gameBackground);
		SetSpriteSize(gameBackSprite_, resources_.getWindowWidth(), resources_.getWindowHeight());
		gameBackSprite_.setColor(gameBackColor_);
	}
}
