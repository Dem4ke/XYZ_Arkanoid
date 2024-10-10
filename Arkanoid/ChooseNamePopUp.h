#pragma once

#include "IMenu.h"
#include "Resources.h"
#include "Math.h"
#include "LeaderBoard.h"

namespace ArkanoidGame {
	// Pop up of choose player's name 
	class ChooseNamePopUp final : public IMenu {
	public:
		ChooseNamePopUp(Resources& resources, GameState& gameState, sf::RenderWindow& window, std::shared_ptr<LeaderBoard> leaderBoard);

		void init() override;
		void reset() override;
		void update(const sf::Event& event) override;
		void draw() override;

		GameStateType getState() override;

	protected:
		// Work tools
		void moveUp();
		void moveDown();

		void enterName(sf::String letter);
		void deleteName();
		void savePlayerInTable();

	private:
		int menuNameTextSize_ = 60;
		int menuButtonsTextSize_ = 40;
		int selectedButton_ = 0;

		float posX_ = 0.f;
		float posY_ = 0.f;

		std::vector<sf::Text> buttons_;
		sf::Text menuName_;

		std::string DefaultPlayerName_ = "XYZ";
		sf::String playerInput_;
		sf::Text playerName_;

		sf::Color mainButtonColor_ = sf::Color::White;
		sf::Color chosenButtonColor_ = sf::Color::Blue;

		Resources& resources_;
		GameState& gameState_;
		sf::RenderWindow& window_;
		std::shared_ptr<LeaderBoard> leaderBoard_;
	};
}