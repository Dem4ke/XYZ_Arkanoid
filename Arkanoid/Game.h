#pragma once

#include "Menu.h"
#include "LeaderBoard.h"
#include "PopUp.h"
#include "GameField.h"
#include "UI.h"

namespace ArkanoidGame {

	class Game {
	public:
		Game(Resources& resources, sf::RenderWindow& window);

		void init();
		void restart();
		void updateMenu(sf::Event& event);
		void update(const float& deltaTime);
		void gameOver();
		void draw();

	private:	
		sf::RenderWindow& window_;
		Resources& resources_;

		GameState gameState_;

		GameField gameField_;

		Menu mainMenu_;
		DifficultyLevelMenu difficultyLevelMenu_;
		OptionsMenu optionsMenu_;
		WindowEditMenu windowEditMenu_;
		ExitMenu exitMenu_;
		PauseMenu pauseMenu_;
		GameOver gameOverMenu_;

		LeaderBoard leaderBoard_;

		GameOverPopUp gameOverPopUp_;
		GameWinPopUp gameWinPopUp_;
		ChooseNamePopUp chooseName_;

		UI UI_;
	};
}