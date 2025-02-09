#include "Game.h"
#include "Settings/Settings.h"

int main()
{
	int Seed = static_cast<int>(time(nullptr));
	srand(Seed);

	// Set game window
	unsigned int WIndowWidth = SETTINGS.GetScreenWidth();
	unsigned int WIndowHeight = SETTINGS.GetScreenHeight();
	sf::RenderWindow Window(sf::VideoMode(WIndowWidth, WIndowHeight), "Arkanoid!");
	
	// Initialization of game object
	Arkanoid::UGame Game;

	// Initialization of clocks
	sf::Clock GameClock;
	float LastTime = GameClock.getElapsedTime().asSeconds();

	// Main loop
	while (Window.isOpen()) 
	{
		// Calculate time delta
		float CurrentTime = GameClock.getElapsedTime().asSeconds();
		float DeltaTime = CurrentTime - LastTime;
		LastTime = CurrentTime;

		// OS state checkout
		sf::Event Event;
		while (Window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed) 
			{
				Window.close();
				break;
			}

			// All menu moves
			Game.EventUpdate(Event);
		}

		// Update main gameplay 
		if (DeltaTime < SETTINGS.GetTimePerFrame())
		{
			// Reduce framerate to not spam CPU and GPU
			sf::sleep(sf::seconds(SETTINGS.GetTimePerFrame() - DeltaTime));
		}

		// Core gameplay update
		Game.GameplayUpdate(SETTINGS.GetTimePerFrame());

		// Draw game
		Window.clear();
		Game.Draw(Window);
		Window.display();
	}

	return 0;
}