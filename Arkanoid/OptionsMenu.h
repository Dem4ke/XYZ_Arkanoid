#pragma once

#include "IMenu.h"
#include "Resources.h"
#include "Math.h"

namespace ArkanoidGame {
	// Menu of options of the game
	class OptionsMenu final : public IMenu {
	public:
		OptionsMenu(Resources& resources, GameState& gameState, sf::RenderWindow& window);
		virtual ~OptionsMenu();

		void init() override;
		void reset() override;
		void update(const sf::Event& event) override;
		void draw() override;

		GameStateType getState() override;

	private:
		// Work tools
		void moveUp();
		void moveDown();
		void changeButton(int index, std::string newButton);

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