#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

namespace ArkanoidGame {
	class Resources {
	public:
		Resources(float width, float height);

		void setTextures();
		void setBackgrounds();
		void setSounds();
		void setFont();

		void changeWindowWidth(float newWidth);
		void changeWindowHeight(float newHeight);

		float getWindowWidth() const;
		float getWindowHeight() const;

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

	private:
		float width_ = 0;
		float height_ = 0;
		const std::string resourcesPath_ = "Resources/";
		const std::string fontsPath_ = "Fonts/";
		const std::string texturesPath_ = "MainTextures/";
		const std::string soundsPath_ = "Sounds/";
		const std::string backgroundsPath_ = "Backgrounds/";
	};
	
	// Sounds and music
	void SetSoundsVolume(Resources& resources, float volume);
	void SetMusicVolume(Resources& resources, float volume);
	void MenuMovementSound(Resources& resources);
	void HitSound(Resources& resources);
	void GameOverSound(Resources& resources);
	void GameWinSound(Resources& resources);
	void SoundOfChoose(Resources& resources);
	void PlayBackMusic(Resources& resources);
	void StopBackMusic(Resources& resources);
}
