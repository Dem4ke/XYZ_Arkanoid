#pragma once

#include <SFML/Graphics.hpp>

namespace Arkanoid
{
	class OGameUI {
	public:
		OGameUI();
		~OGameUI() = default;
		
		void SetScore(int Value);
		void SetBallLifes(int Value);
		void Draw(sf::RenderWindow& Window);

	private:
		int TextSize = 60;				// Text size
		std::vector<sf::Text> Text;		// Vector of all text on screen
	};
}