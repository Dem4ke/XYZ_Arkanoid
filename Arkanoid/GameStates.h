#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>

namespace ArkanoidGame {

	enum class DifficultyLevel : int {
		None = 0,
		Easy,
		Medium,
		Hard,
	};

	enum class GameStateType : int {
		None = 0,
		MainMenu,
		GameReset,
		Game,
		Pause,
		GameOver,
		LeaderBoard,
		DifficulityLevelChoose,
		Options,
		WindowSizeEdit,
		ChangeResolution,
		ExitDialog,
		PlayAgain,
		GameOverPopUp,
		ChooseNameOfPlayer,
	};

	class Data {
	public:
		bool deserialize(std::vector<std::pair<std::string, int>>& info);
		bool serialize(std::vector<std::pair<std::string, int>>& info);

	private:
		void open(std::string fileName);
		void close();

		const std::string dataPath_ = "Data/";
		const std::string leaderBoard_ = "LeaderTable.txt";
		std::fstream workWithData_;
	};

	class GameState {
	public: 
		GameState();

		void scoreIncrease(int cost);
		void reset();
		
		void pushGameState(GameStateType newType);
		void popGameState();
		void restartGameState();

		void setPlayerName(std::string playerName);
		std::string getPlayerName() const;

		int getScore() const;
		GameStateType getCurrentGameState() const;

		// Difficulty 
		DifficultyLevel getCurrentDiffLvl() const;
		void setNewDifficulty(DifficultyLevel newDifficulty);

		// Work with files
		void deserialize(std::vector<std::pair<std::string, int>>& info);
		void serialize(std::vector<std::pair<std::string, int>>& info);

	private:
		Data data_;

		DifficultyLevel diffLvl_ = DifficultyLevel::Easy;

		std::string DefaultPlayerName_ = "XYZ";
		std::string playerName_ = "XYZ";
		int score_ = 0;

		GameStateType gameStateType = GameStateType::None;
		std::vector<GameStateType> gameStatesStack;
	};
}
