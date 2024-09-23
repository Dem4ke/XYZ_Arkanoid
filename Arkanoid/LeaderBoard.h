#pragma once

#include <unordered_map>
#include <algorithm>

#include "IMenu.h"
#include "Resources.h"
#include "Math.h"

namespace ArkanoidGame {
	// Leader board menu
	class LeaderBoard : public IMenu {
	public:
		LeaderBoard(Resources& resources, GameState& gameState, sf::RenderWindow& window);
		virtual ~LeaderBoard();

		void init() override;
		void reset() override;
		void update(const sf::Event& event) override;
		void sortTable();
		void addPlayer();
		void saveTable();
		void draw() override;

		GameStateType getState() override;

	protected:
		int menuNameTextSize_ = 60;
		int menuButtonsTextSize_ = 40;
		int drawablePositions_ = 8;

		float posX_ = 0;
		float posY_ = 0;

		sf::Text playerName_;
		sf::Text playerScore_;
		sf::Text menuName_;
		sf::Color mainButtonColor_ = sf::Color::White;

		std::vector<std::pair<std::string, int>> tableText_;
		std::vector<std::pair<sf::Text, sf::Text>> liderBoard_;

		Resources& resources_;
		GameState& gameState_;
		sf::RenderWindow& window_;
	};

	class ShortLeaderBoard final : public LeaderBoard {
	public:
		ShortLeaderBoard(Resources& resources, GameState& gameState, sf::RenderWindow& window);
		virtual ~ShortLeaderBoard();

		void init() override;
		void draw() override;

		GameStateType getState() override;

	private:
		int drawablePositions_ = 5;
	};
}