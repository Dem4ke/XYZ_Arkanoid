#pragma once

#include <unordered_map>
#include <algorithm>

#include "GameStates.h"
#include "Resources.h"
#include "Math.h"

namespace ArkanoidGame {

	// Leader board menu
	class LeaderBoard {
	public:
		LeaderBoard(Resources& resources, GameState& gameState, sf::RenderWindow& window);

		void init(std::string menuName, float buttonSize = 40.f, int drawablePositions = 8);
		void update(const sf::Event& event);
		void sortTable();
		void addPlayer();
		void saveTable();
		void drawLongBoard();
		void drawShortBoard();

	private:
		int drawablePositions_ = 0;
		int shortDrawablePos_ = 0;

		float posX_ = 0;
		float posY_ = 0;
		float buttonSize_ = 0;

		sf::Text playerName_;
		sf::Text playerScore_;
		sf::Text menuName_;

		std::vector<std::pair<std::string, int>> tableText_;
		std::vector<std::pair<sf::Text, sf::Text>> liderBoard_;

		sf::Color mainButtonColor_ = sf::Color::White;
		sf::Sprite backgroundSprite_;

		sf::Keyboard::Key escapeKey_ = sf::Keyboard::B;

		Resources& resources_;
		GameState& gameState_;
		sf::RenderWindow& window_;
	};
}