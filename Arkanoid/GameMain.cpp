#include "Game.h"

int main() {
	int seed = static_cast <int> (time(nullptr));
	srand(seed);

	// Game initialization
	ArkanoidGame::Resources resources{ 800.f, 600.f };
	sf::RenderWindow window(sf::VideoMode(static_cast<unsigned int> (resources.getWindowWidth()), static_cast<unsigned int> (resources.getWindowHeight())), "Arcanoid!");

	ArkanoidGame::Game game{ resources, window };

	game.init();

	// Initialization of clocks
	sf::Clock gameClock;
	float lastTime = gameClock.getElapsedTime().asSeconds();

	// Main loop
	while (window.isOpen()) {

		// Calculate time delta
		float currentTime = gameClock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// OS state checkout
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				break;
			}

			// All menu moves
			game.updateMenu(event);
		}

		// Update main gameplay 
		if (deltaTime < resources.getFrameRate()) {
			// Reduce framerate to not spam CPU and GPU
			sf::sleep(sf::seconds(resources.getFrameRate() - deltaTime));
		}

		game.update(resources.getFrameRate());
		game.gameOver();

		// Draw game
		window.clear();
		game.draw();
		window.display();
	}

	return 0;
}