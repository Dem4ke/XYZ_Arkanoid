#include "GameStates.h"

namespace ArkanoidGame {
	
	// DATA
	
	// Get gamestate from file
	bool Data::deserialize(std::vector<std::pair<std::string, int>>& info) {
		open(leaderBoard_);

		if (workWithData_.is_open()) {
			info.clear();

			std::string name;
			int score;

			while (workWithData_ >> name >> score) {
				info.push_back({ name, score });
			}

			close();
			return true;
		}

		return false;
	}

	// Save gamestate in file
	bool Data::serialize(std::vector<std::pair<std::string, int>>& info) {
		open(leaderBoard_);

		if (workWithData_.is_open()) {

			for (const auto& i : info) {
				workWithData_ << i.first << " " << i.second << std::endl;
			}

			close();
			return true;
		}

		return false;
	}

	//----------------------------------------------------------
	// PRIVATE TOOLBOX

	// Open filestream
	void Data::open(std::string fileName) {
		workWithData_.open(dataPath_ + fileName);
	}

	// Close filestream
	void Data::close() {
		workWithData_.close();
	}

	//----------------------------------------------------------
	// GAMESTATE
	GameState::GameState() {}

	// Increase apples counter when apple has been eaten
	void GameState::scoreIncrease(int cost) {
		score_ += cost;
	}

	// Reset apples counter when game has been restarted
	void GameState::reset() {
		score_ = 0;
		playerName_ = DefaultPlayerName_;
	}

	// Add a new game state in "game states stack"
	void GameState::pushGameState(GameStateType newType) {
		gameStatesStack.push_back(newType);
		gameStateType = gameStatesStack[gameStatesStack.size() - 1];
	}

	// Delete current game state from "game states stack"
	void GameState::popGameState() {
		gameStatesStack.pop_back();
		gameStateType = gameStatesStack[gameStatesStack.size() - 1];
	}

	// Clear "game states stack" and set main menu
	void GameState::restartGameState() {
		gameStatesStack.clear();
		pushGameState(GameStateType::MainMenu);
	}

	// Set name to player to save it in leader board
	void GameState::setPlayerName(std::string playerName) {
		playerName_ = playerName;
	}

	std::string GameState::getPlayerName() const { return playerName_; }

	int GameState::getScore() const { return score_; }

	GameStateType GameState::getCurrentGameState() const { return gameStateType; }

	DifficultyLevel GameState::getCurrentDiffLvl() const { return diffLvl_; }

	void GameState::setNewDifficulty(DifficultyLevel newDifficulty) {
		diffLvl_ = newDifficulty;
	}

	void GameState::deserialize(std::vector<std::pair<std::string, int>>& info){
		if (!data_.deserialize(info)) {
			// show on screen "game was not load"
		}
	}

	void GameState::serialize(std::vector<std::pair<std::string, int>>& info) {
		if (!data_.serialize(info)) {
			// show on screen "game was not save"
		}
	}
}