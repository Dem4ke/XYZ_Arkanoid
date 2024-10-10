#include <cassert>
#include "Resources.h"

namespace ArkanoidGame {
	Resources::Resources(float width, float height) : width_(width), height_(height) {
		setTextures();
		setBackgrounds();
		setSounds();
		setFont();
	}

	// Load texures from resources path
	void Resources::setTextures() {
		bool isLoaded = normalBlock.loadFromFile(resourcesPath_ + texturesPath_ + "blocks_bricks.png");
		assert(isLoaded);
	}

	// Loads backgrounds from resources path
	void Resources::setBackgrounds() {
		bool isLoaded = mainMenuBackground.loadFromFile(resourcesPath_ + backgroundsPath_ + "Main_background.jpg");
		assert(isLoaded);

		isLoaded = gameBackground.loadFromFile(resourcesPath_ + backgroundsPath_ + "Main_background.jpg");
		assert(isLoaded);
	}

	// Load sounds from resources path
	void Resources::setSounds() {
		// Little sounds
		bool isLoaded = menuMove.loadFromFile(resourcesPath_ + soundsPath_ + "Owlstorm__Snake_hit.wav");
		assert(isLoaded);

		isLoaded = gameOverSound.loadFromFile(resourcesPath_ + soundsPath_ + "Maodin204__Lose.wav");
		assert(isLoaded);

		isLoaded = hitSound.loadFromFile(resourcesPath_ + soundsPath_ + "Owlstorm__Snake_hit.wav");
		assert(isLoaded);

		isLoaded = soundOfChoose.loadFromFile(resourcesPath_ + soundsPath_ + "Theevilsocks__menu-hover.wav");
		assert(isLoaded);

		// Long sounds or background music (not loads file but opens it for a whole session)
		isLoaded = backMusic.openFromFile(resourcesPath_ + soundsPath_ + "Clinthammer__Background_Music.wav");
		assert(isLoaded);
	}

	// Load fonts from resources path
	void Resources::setFont() {
		bool isLoaded = font.loadFromFile(resourcesPath_ + fontsPath_ + "Roboto-Regular.ttf");
		assert(isLoaded);
	}

	void Resources::changeWindowWidth(float newWidth) { width_ = newWidth; }

	void Resources::changeWindowHeight(float newHeight) { height_ = newHeight; }

	float Resources::getWindowWidth() const { return width_; }

	float Resources::getWindowHeight() const { return height_; }

	float Resources::getFrameRate() const { return frameRate_; }

	// SOUNDS AND MUSIC 
	
	// Change volume of sounds
	void SetSoundsVolume(Resources& resources, float volume) {
		resources.sound.setVolume(volume);
	}
	// Change volume of music
	void SetMusicVolume(Resources& resources, float volume) {
		resources.backMusic.setVolume(volume);
	}

	// Init sound of menu move
	void MenuMovementSound(Resources& resources) {
		resources.sound.setBuffer(resources.menuMove);
		resources.sound.play();
	}

	// Init hit sound and play
	void HitSound(Resources& resources) {
		resources.sound.setBuffer(resources.hitSound);
		resources.sound.play();
	}

	// Init game over sound and play
	void GameOverSound(Resources& resources) {
		resources.sound.setBuffer(resources.gameOverSound);
		resources.sound.play();
	}

	void GameWinSound(Resources& resources) {
		resources.sound.setBuffer(resources.gameOverSound);
		resources.sound.play();
	}

	// Init sound of a click on any button
	void SoundOfChoose(Resources& resources) {
		resources.sound.setBuffer(resources.soundOfChoose);
		resources.sound.play();
	}

	// Start playing background music 
	void PlayBackMusic(Resources& resources) {
		resources.backMusic.play();
		resources.backMusic.setLoop(true);
	}

	// Stop playing background music
	void StopBackMusic(Resources& resources) {
		resources.backMusic.pause();
	}
}