#pragma once

#include "IMenu.h"
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
		UI UI_;

		std::vector<std::shared_ptr<IMenu>> menus_;
		std::vector<std::shared_ptr<IMenu>> popUps_;
	};
}