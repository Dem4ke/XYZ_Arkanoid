#pragma once

#include "IMenu.h"
#include "Resources.h"
#include "Math.h"

namespace ArkanoidGame {
	// Menu of choice difficulty of the game
	class DifficultyLevelMenu final : public IMenu {
	public:
		DifficultyLevelMenu(Resources& resources, GameState& gameState, sf::RenderWindow& window);
		virtual ~DifficultyLevelMenu();

		void init() override;
		void reset() override;
		void update(const sf::Event& event) override;
		void draw() override;

	private:
		// Work tools
		void moveUp() override;
		void moveDown() override;

	private:
		int menuNameTextSize_ = 60;
		int menuButtonsTextSize_ = 40;
		int selectedButton_ = 0;

		std::vector<sf::Text> buttons_;
		sf::Text menuName_;

		sf::Color mainButtonColor_ = sf::Color::White;
		sf::Color chosenButtonColor_ = sf::Color::Blue;

		Resources& resources_;
		GameState& gameState_;
		sf::RenderWindow& window_;
	};
}