#pragma once

#include "GameStates.h"
#include "GameStatesData.h"
#include "Resources.h"
#include "Math.h"

namespace ArkanoidGame {
	
	// Standart menu 
	class MainMenu final : public GameStatesData {
	public:
		MainMenu(Resources& resources, GameState& gameState, sf::RenderWindow& window);
		virtual ~MainMenu();

		void init() override;
		void reset() override;
		void update(const sf::Event& event) override;
		void draw() override;

	private:
		// Work tools
		void moveUp() override;
		void moveDown() override;

		Resources& resources_;
		GameState& gameState_;
		sf::RenderWindow& window_;
	};

	// Options menu
	class OptionsMenu final : public Menu {
	public:
		OptionsMenu(Resources& resources, GameState& gameState, sf::RenderWindow& window);
		virtual ~OptionsMenu() {}

		void update(const sf::Event& event) override;

	private:
		void changeButton(int index, std::string newButton);
	};

	// Menu of choice difficulty of levels
	class DifficultyLevelMenu final : public Menu {
	public:
		DifficultyLevelMenu(Resources& resources, GameState& gameState, sf::RenderWindow& window);
		virtual ~DifficultyLevelMenu() {}

		void update(const sf::Event& event) override;
	};

	// Menu to change window's size
	class WindowEditMenu final : public Menu {
	public:
		WindowEditMenu(Resources& resources, GameState& gameState, sf::RenderWindow& window);
		virtual ~WindowEditMenu() {}

		void update(const sf::Event& event) override;
	};

	// Menu to exit from game
	class ExitMenu final : public Menu {
	public:
		ExitMenu(Resources& resources, GameState& gameState, sf::RenderWindow& window);
		virtual ~ExitMenu() {}

		void update(const sf::Event& event) override;
	};

	// Menu of pause
	class PauseMenu final : public Menu {
	public:
		PauseMenu(Resources& resources, GameState& gameState, sf::RenderWindow& window);
		virtual ~PauseMenu() {}

		void update(const sf::Event& event) override;
	};

	// Menu of game over
	class GameOver final : public Menu {
	public:
		GameOver(Resources& resources, GameState& gameState, sf::RenderWindow& window);
		virtual ~GameOver() {}

		void update(const sf::Event& event) override;
	};

	// Toolbox functions
	void ExitInPauseMenu(GameState& gameState);
}
