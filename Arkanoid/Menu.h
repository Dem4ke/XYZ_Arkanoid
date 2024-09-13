#pragma once

#include "GameStates.h"
#include "Resources.h"
#include "Math.h"

namespace ArkanoidGame {
	
	// Standart menu 
	class Menu {
	public:
		Menu(Resources& resources, GameState& gameState, sf::RenderWindow& window);
		virtual ~Menu() {}

		virtual void init(std::string menuName, std::vector<std::string>& allButtons,
			float buttonSize = 40.f, sf::Color colorOfButtons = sf::Color::White);
		virtual void reset();
		virtual void update(const sf::Event& event);
		virtual void draw();

	protected:
		// Work tools
		void moveUp();
		void moveDown();

		int selectedButton_ = 0;

		std::vector<sf::Text> buttons_;
		sf::Text menuName_;

		sf::Color mainButtonColor_ = sf::Color::White;
		sf::Color chosenButtonColor_ = sf::Color::Blue;

		sf::Sprite backgroundSprite_;

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
