#include "Game.h"

namespace ArkanoidGame {

	Game::Game(Resources& resources, sf::RenderWindow& window) :
		resources_(resources), window_(window),
		mainMenu_(resources, gameState_, window),
		difficultyLevelMenu_(resources, gameState_, window),
		optionsMenu_(resources, gameState_, window),
		exitMenu_(resources, gameState_, window),
		pauseMenu_(resources, gameState_, window),
		gameOverMenu_(resources, gameState_, window),
		leaderBoard_(resources, gameState_, window),
		windowEditMenu_(resources, gameState_, window),
		gameOverPopUp_(resources, gameState_, window),
		chooseName_(resources, gameState_, window, leaderBoard_),
		UI_(resources, gameState_, window),
		gameField_(resources, gameState_, window) {}

	void Game::init() {
		std::vector<std::string> mainButtons = { "Play game", "Difficulity level", "Leader board", "Options", "Exit" };
		std::vector<std::string> dufficulityLevelButtons = { "Easy", "Medium", "Hard" };
		std::vector<std::string> optionsButtons = { "Music: On", "Sounds: On", "Window size "};
		std::vector<std::string> windowEditButtons = { "800 x 600", "1280 x 720", "1920 x 1080"};
		std::vector<std::string> exitButtons = { "Yes", "No" };
		std::vector<std::string> pauseButtons = { "Yes", "No" };
		std::vector<std::string> gameOverButtons = { "\n\n\n\n\n\n\n\nPlay again", "\n\n\n\n\n\n\n\nExit"};
		std::vector<std::string> gameOverPopUpButtons = { "No", "Yes" };
		std::vector<std::string> chooseNamePopUpButtons = { "\n\nEnter" };

		// Menu initialization (Name of menu, vector of buttons, size of buttons (40.f by default), color of buttons (white by default))
		// Name of menu will be in 1.5 bigger, id of menu needs for choose of background
		mainMenu_.init("Arcanoid", mainButtons);
		difficultyLevelMenu_.init("Difficulity level", dufficulityLevelButtons);
		optionsMenu_.init("Options", optionsButtons);
		windowEditMenu_.init("Edit window size", windowEditButtons);
		exitMenu_.init("Do you want to exit?", exitButtons);
		pauseMenu_.init("Do you want to exit\n\tin main menu?\n", pauseButtons);
		gameOverMenu_.init("Game Over\n\n\n", gameOverButtons);

		// Leader board initialization (Name of menu, size of names, number of drawable positions)
		leaderBoard_.init("Leader Board");

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

		restart();
	}

	void Game::restart() {
		// Reset game state 
		gameState_.restartGameState();

		// Reset menus
		mainMenu_.reset();
		difficultyLevelMenu_.reset();
		optionsMenu_.reset();
		exitMenu_.reset();
		pauseMenu_.reset();
		gameOverMenu_.reset();

		// Load leader board from file and sort it
		leaderBoard_.sortTable();

		// Reset score and player name
		gameState_.reset();
		UI_.scoreUpdate();

		// Reset pop ups
		gameOverPopUp_.reset();
		chooseName_.reset();

		// Initialization of the game field
		gameField_.reset();
	}

	// Update menu states, it works only with Event
	void Game::updateMenu(sf::Event& event) {
		switch (gameState_.getCurrentGameState()) {
		case GameStateType::MainMenu: {
			mainMenu_.update(event);
			break;
		}
		case GameStateType::DifficulityLevelChoose: {
			difficultyLevelMenu_.update(event);
			break;
		}
		case GameStateType::Options: {
			optionsMenu_.update(event);
			break;
		}
		case GameStateType::WindowSizeEdit: {
			windowEditMenu_.update(event);
			break;
		}
		case GameStateType::ExitDialog: {
			exitMenu_.update(event);
			break;
		}
		case GameStateType::Pause: {
			pauseMenu_.update(event);
			break;
		}
		case GameStateType::LeaderBoard: {
			leaderBoard_.update(event);
			break;
		}
		case GameStateType::GameOver: {
			gameOverMenu_.update(event);
			break;
		}
		case GameStateType::GameOverPopUp: {
			gameOverPopUp_.update(event);
			break;
		}
		case GameStateType::ChooseNameOfPlayer: {
			chooseName_.update(event);
			break;
		}
		}
	}

	// Update only game process 
	void Game::update(const float& deltaTime) {
		if (gameState_.getCurrentGameState() == GameStateType::Game) {

			// Update main game process
			gameField_.update(deltaTime);
			
			// Pause menu maker
			ExitInPauseMenu(gameState_);

			// Update player's score
			UI_.scoreUpdate();
		}
	}

	void Game::gameOver() {
		switch (gameState_.getCurrentGameState()) {
		case GameStateType::GameOver: {
			leaderBoard_.sortTable();
			break;
		}
		case GameStateType::PlayAgain: {
			restart();
			gameState_.pushGameState(GameStateType::Game);
			break;
		}
		case GameStateType::GameReset: {
			restart();
			break;
		}
		case GameStateType::ChangeResolution: {
			init();
			gameState_.pushGameState(GameStateType::Options);
			gameState_.pushGameState(GameStateType::WindowSizeEdit);
		}
		}
	}

	void Game::draw() {
		switch (gameState_.getCurrentGameState()) {
		case GameStateType::MainMenu: {
			mainMenu_.draw();
			break;
		}
		case GameStateType::DifficulityLevelChoose: {
			difficultyLevelMenu_.draw();
			break;
		}
		case GameStateType::Options: {
			optionsMenu_.draw();
			break;
		}
		case GameStateType::WindowSizeEdit: {
			windowEditMenu_.draw();
			break;
		}
		case GameStateType::ExitDialog: {
			exitMenu_.draw();
			break;
		}
		case GameStateType::Pause: {
			gameField_.draw();
			pauseMenu_.draw();
			break;
		}
		case GameStateType::LeaderBoard: {
			leaderBoard_.drawLongBoard();
			break;
		}
		case GameStateType::GameOver: {
			gameField_.draw();
			gameOverMenu_.draw();
			leaderBoard_.drawShortBoard();
			break;
		}
		case GameStateType::GameOverPopUp: {
			gameField_.draw();
			gameOverPopUp_.draw();
			UI_.drawGameOver();
			break;
		}
		case GameStateType::ChooseNameOfPlayer: {
			gameField_.draw();
			chooseName_.draw();
			UI_.drawGameOver();
			break;
		}
		case GameStateType::Game: {
			gameField_.draw();
			UI_.drawMain();
			break;
		}
		}
	}
}