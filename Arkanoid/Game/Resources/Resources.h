#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Arkanoid
{
	// Class which works with assets
	class UResources
	{
	public:
		UResources();

		void setTextures();
		void setBackgrounds();
		void setSounds();
		void setFont();

	private:
		sf::Texture mainMenuBackground;
		sf::Texture gameBackground;
		sf::Texture normalBlock;

		sf::SoundBuffer menuMove;
		sf::SoundBuffer gameOverSound;
		sf::SoundBuffer hitSound;
		sf::SoundBuffer soundOfChoose;

		sf::Music backMusic;
		sf::Sound sound;
		sf::Font font;
	};
}
