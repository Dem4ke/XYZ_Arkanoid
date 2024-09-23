#include "Game.h"
#include "MainMenu.h"
#include "DifficultyLevelMenu.h"
#include "ExitMenu.h"
#include "GameOverMenu.h"
#include "LeaderBoard.h"
#include "OptionsMenu.h"
#include "PauseMenu.h"
#include "WindowPropertyMenu.h"
#include "ChooseNamePopUp.h"
#include "GameWinPopUp.h"
#include "GameOverPopUp.h"

namespace ArkanoidGame {

	Game::Game(Resources& resources, sf::RenderWindow& window) :
		resources_(resources), window_(window),
		UI_(resources, gameState_, window),
		gameField_(resources, gameState_, window) {}

	void Game::init() {
		menus_.clear();
		// Initialization of menus
		menus_.emplace_back(std::make_shared<MainMenu>(resources_, gameState_, window_));
		menus_.emplace_back(std::make_shared<DifficultyLevelMenu>(resources_, gameState_, window_));
		menus_.emplace_back(std::make_shared<ExitMenu>(resources_, gameState_, window_));
		menus_.emplace_back(std::make_shared<GameOverMenu>(resources_, gameState_, window_));
		menus_.emplace_back(std::make_shared<OptionsMenu>(resources_, gameState_, window_));
		menus_.emplace_back(std::make_shared<PauseMenu>(resources_, gameState_, window_));
		menus_.emplace_back(std::make_shared<LeaderBoard>(resources_, gameState_, window_));
		menus_.emplace_back(std::make_shared<ShortLeaderBoard>(resources_, gameState_, window_));
		menus_.emplace_back(std::make_shared<WindowPropertyMenu>(resources_, gameState_, window_));

		popUps_.clear();
		// Initialization of pop ups
		std::shared_ptr<LeaderBoard> leaderBoard = std::static_pointer_cast<LeaderBoard>(menus_[6]);
		popUps_.emplace_back(std::make_shared<ChooseNamePopUp>(resources_, gameState_, window_, leaderBoard));
		popUps_.emplace_back(std::make_shared<GameWinPopUp>(resources_, gameState_, window_));
		popUps_.emplace_back(std::make_shared<GameOverPopUp>(resources_, gameState_, window_));

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

		// All menus and pop ups reset
		static auto resetFunctor = [](auto obj) {
			obj->reset();
		};

		std::for_each(menus_.begin(), menus_.end(), resetFunctor);
		std::for_each(popUps_.begin(), popUps_.end(), resetFunctor);

		// Reset score and player name
		gameState_.reset();
		UI_.scoreUpdate();

		// Initialization of the game field
		gameField_.reset();
	}

	// Update menu states, it works only with Event
	void Game::updateMenu(sf::Event& event) {
		for (int i = 0, end = menus_.size(); i < end; ++i) {
			if (menus_[i]->getState() == gameState_.getCurrentGameState()) {
				menus_[i]->update(event);
				break;
			}
		}

		for (int i = 0, end = popUps_.size(); i < end; ++i) {
			if (popUps_[i]->getState() == gameState_.getCurrentGameState()) {
				popUps_[i]->update(event);
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
			std::shared_ptr<PauseMenu> pauseMenu = std::static_pointer_cast<PauseMenu>(menus_[5]);
			pauseMenu->callMenu();

			// Update player's score
			UI_.scoreUpdate();
		}
	}

	void Game::gameOver() {
		switch (gameState_.getCurrentGameState()) {
		case GameStateType::GameOver: {
			std::shared_ptr<LeaderBoard> leaderBoard = std::static_pointer_cast<LeaderBoard>(menus_[6]);
			std::shared_ptr<ShortLeaderBoard> shortLeaderBoard = std::static_pointer_cast<ShortLeaderBoard>(menus_[7]);
			leaderBoard->sortTable();
			shortLeaderBoard->sortTable();
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
		// Draw everything except menus and popups
		switch (gameState_.getCurrentGameState()) {
		case GameStateType::Pause: {
			gameField_.draw();
			break;
		}
		case GameStateType::GameOver: {
			gameField_.draw();
			break;
		}
		case GameStateType::GameOverPopUp: {
			gameField_.draw();
			UI_.drawGameOver();
			break;
		}
		case GameStateType::GameWinPopUp: {
			gameField_.draw();
			UI_.drawGameOver();
			break;
		}
		case GameStateType::ChooseNameOfPlayer: {
			gameField_.draw();
			UI_.drawGameOver();
			break;
		}
		case GameStateType::Game: {
			gameField_.draw();
			UI_.drawMain();
			break;
		}
		}

		// Draw all menus
		for (int i = 0, end = menus_.size(); i < end; ++i) {
			if (menus_[i]->getState() == gameState_.getCurrentGameState()) {
				menus_[i]->draw();
			}
		}

		// Draw all pop ups
		for (int i = 0, end = popUps_.size(); i < end; ++i) {
			if (popUps_[i]->getState() == gameState_.getCurrentGameState()) {
				popUps_[i]->draw();
			}
		}
	}
}