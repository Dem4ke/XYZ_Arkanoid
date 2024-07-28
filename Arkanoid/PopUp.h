#pragma once

#include "Menu.h"
#include "LeaderBoard.h"

namespace SnakeGame {

	// Game ended pop up
	class PopUp : public Menu {
	public:
		PopUp(Resources& resources);

		void init(std::string popUpName, std::vector<std::string>& allButtons,
			float buttonSize = 40.f, sf::Color colorOfButtons = sf::Color::White) override;
		void reset() override;

		void enterName(sf::String letter);
		void deleteName();
		void savePlayerInTable(GameState& gameState);

		sf::Text getPlayerName();
		int getPositionsCount() const;

	private:
		int drawablePositions_ = 4;

		float buttonSize_ = 0;
		float posX_ = 0;
		float posY_ = 0;

		std::string DefaultPlayerName_ = "XYZ";
		sf::String playerInput_;
		sf::Text playerName_;
	};

	// Pop up movement
	void GameOverPopUpMovement(PopUp& popUp, GameState& gameState, const sf::Event& event);
	void ChooseNamePopUpMovement(PopUp& popUp, GameState& gameState, LeaderBoard& leaderBoard, const sf::Event& event);

	// Draw pop ups
	void DrawPopUp(PopUp& popUp, sf::RenderWindow& window, GameState& gameState);
}