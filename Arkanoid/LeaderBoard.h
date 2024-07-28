#pragma once

#include <unordered_map>
#include <algorithm>

#include "GameStates.h"
#include "Resources.h"

namespace SnakeGame {

	// Leader board menu
	class LeaderBoard {
	public:
		LeaderBoard(Resources& resources) : resources_(resources) {}

		void init(std::string menuName, float buttonSize, int drawablePositions, GameState& gameState);
		void sortTable(GameState& gameState);
		void addPlayer(GameState& gameState);
		void saveTable(GameState& gameState);

		int getPositionsCount() const;
		int getShortPosCount() const;

		sf::Text getName(int num) const;
		sf::Text getScore(int num) const;
		sf::Text getGeneralName() const;

		sf::Sprite getBackground() const;
		sf::Keyboard::Key getEscapeKey() const;

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
	};

	// Leader board movement
	void LeaderBoardMovement(LeaderBoard& leaderBoard, GameState& gameState, const sf::Event& event);

	// Draw leader boards
	void DrawLeaderBoard(LeaderBoard& leaderBoard, sf::RenderWindow& window);
	void DrawGameOverLeaderBoard(LeaderBoard& leaderBoard, sf::RenderWindow& window);
}