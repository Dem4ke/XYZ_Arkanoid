#pragma once

#include "LeaderBoard.h"

namespace ArkanoidGame {

	// Standart pop up
	class PopUp {
	public:
		PopUp(Resources& resources, GameState& gameState, sf::RenderWindow& window);
		virtual ~PopUp() {}

		virtual void init(std::string popUpName, std::vector<std::string>& allButtons,
			float buttonSize = 40.f, sf::Color colorOfButtons = sf::Color::White);
		virtual void update(const sf::Event& event) = 0;
		virtual void reset();
		virtual void draw();

	protected:
		// Work tools
		void moveUp();
		void moveDown();

		int selectedButton_ = 0;

		float buttonSize_ = 0.f;
		float posX_ = 0.f;
		float posY_ = 0.f;

		std::vector<sf::Text> buttons_;
		sf::Text popUpName_;

		sf::Color mainButtonColor_ = sf::Color::White;
		sf::Color chosenButtonColor_ = sf::Color::Blue;

		sf::Keyboard::Key upKey_ = sf::Keyboard::W;
		sf::Keyboard::Key downKey_ = sf::Keyboard::S;
		sf::Keyboard::Key leftKey_ = sf::Keyboard::A;
		sf::Keyboard::Key rightKey_ = sf::Keyboard::D;
		sf::Keyboard::Key escapeKey_ = sf::Keyboard::B;
		sf::Keyboard::Key enterKey_ = sf::Keyboard::Enter;

		Resources& resources_;
		GameState& gameState_;
		sf::RenderWindow& window_;
	};

	// Pop up of choose player's name 
	class ChooseNamePopUp : public PopUp {
	public:
		ChooseNamePopUp(Resources& resources, GameState& gameState, sf::RenderWindow& window, LeaderBoard& leaderBoard);
		virtual ~ChooseNamePopUp() {}

		void init(std::string popUpName, std::vector<std::string>& allButtons,
			float buttonSize = 40.f, sf::Color colorOfButtons = sf::Color::White) override;
		void reset() override;
		void update(const sf::Event& event) override;
		void draw() override;

	private:
		void enterName(sf::String letter);
		void deleteName();
		void savePlayerInTable();

		std::string DefaultPlayerName_ = "XYZ";
		sf::String playerInput_;
		sf::Text playerName_;

		LeaderBoard& leaderBoard_;
	};

	// Game over pop up
	class GameOverPopUp : public PopUp {
	public:
		GameOverPopUp(Resources& resources, GameState& gameState, sf::RenderWindow& window);
		virtual ~GameOverPopUp() {}

		void update(const sf::Event& event) override;
	};
}