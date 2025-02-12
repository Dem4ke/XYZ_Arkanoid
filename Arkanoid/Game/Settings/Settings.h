#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Arkanoid
{
	// Structure which contains factor of scale for all objects on the screen
	struct CScaleFactor
	{
		float X = 1.f;	
		float Y = 1.f;
	};

	// Structure to work with common assets
	struct CResources
	{
	public:
		CResources();
		
		void SetSoundsVolume(float Value);
		void SetBackgroundMusicVolume(float Value);
		void PlaySound(sf::SoundBuffer& SoundAsset);
		void PlayBackgroundMusic();
		void StopBackgroundMusic();

		const sf::Font& GetFont();

	private:
		sf::Sound Sound;
		sf::Music BackgroundMusic;
		sf::Font Font;
	};

	// Class for work with game settings which player can change
	class UGameSettings
	{
	private:
		UGameSettings();
		~UGameSettings() = default;

	public:
		static UGameSettings& Instance();

		void SaveSettings();
		void SetScreenWidth(int Value);
		void SetScreenHeight(int Value);

		void SetTimePerFrame(float Value);
		void SetSoundPower(float Value);

		void SetFullscreenMode(bool bIsOn);
		void SetSoundsOn(bool bIsOn); 
		void SetMusicOn(bool bIsOn);

		int GetScreenWidth() const;
		int GetScreenHeight() const;

		float GetTimePerFrame() const;
		float GetSoundPower() const;

		bool IsFullscreenMode() const;
		bool IsSoundsOn() const;
		bool IsMusicOn() const;

		const CScaleFactor& GetScaleFactor();
		CResources* GetResources();

	private:		
		int ScreenWidth = 0;				// Width of rendered window
		int ScreenHeight = 0;				// Height of rendered window

		float TimePerFrame = 0.f;			// Frame rate limit which user sets in settings
		float SoundPower = 0.f;				// Power of sounds in the game
		float MusicPower = 0.f;				// Power of music in the game

		bool bIsFullscreen = true;			// Flag which contains informaion is fullscreen mode on
		bool bIsSoundsOn = true;			// Flag which contains informaion is sounds on
		bool bIsMusicOn = true;				// Flag which contains informaion is music on

		// Path to config (settings) file
		const std::string PathToConfig = "Config/GameSettings.conf";		

		CScaleFactor ScaleFactor;
		CResources Resources;
	};
}

#define SETTINGS Arkanoid::UGameSettings::Instance()