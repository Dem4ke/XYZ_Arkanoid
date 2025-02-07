#include "Game.h"
#include "Settings/Settings.h"

int main()
{
	int Seed = static_cast<int>(time(nullptr));
	srand(Seed);

	// Construct UGameSettings at first time and load configurate file
	Arkanoid::UGameSettings* GameSettings = Arkanoid::UGameSettings::GetGameSettings();

	// Set game window
	unsigned int WIndowWidth = GameSettings->GetScreenWidth();
	unsigned int WIndowHeight = GameSettings->GetScreenHeight();
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
		if (DeltaTime < GameSettings->GetTimePerFrame())
		{
			// Reduce framerate to not spam CPU and GPU
			sf::sleep(sf::seconds(GameSettings->GetTimePerFrame() - DeltaTime));
		}

		// Core gameplay update
		Game.GameplayUpdate(GameSettings->GetTimePerFrame());

		// Draw game
		Window.clear();
		Game.Draw(Window);
		Window.display();
	}

	return 0;
}