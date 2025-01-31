#pragma once
#include <string>

namespace Arkanoid
{
	// Structure which contains factor of scale for all objects on the screen
	struct CScaleFactor
	{
		float X = 1.f;	
		float Y = 1.f;
	};

	// Class for work with game settings which player can change
	class UGameSettings
	{
	public:
		static UGameSettings* GetGameSettings();

		void SaveSettings();
		void SetScreenWidth(int Value);
		void SetScreenHeight(int Value);
		void SetTimePerFrame(float Value);
		void SetSoundPower(float Value);

		int GetScreenWidth() const;
		int GetScreenHeight() const;
		float GetTimePerFrame() const;
		float GetSoundPower() const;

		const CScaleFactor& GetScaleFactor();

	private:
		UGameSettings();
		static UGameSettings* GameSettings;	// Pointer to only one UGameSettings object;
		
		int ScreenWidth = 0;				// Width of rendered window
		int ScreenHeight = 0;				// Height of rendered window

		float TimePerFrame = 0.f;			// Frame rate limit which user sets in settings
		float SoundPower = 0.f;				// Power of sounds in the game

		// Path to config (settings) file
		const std::string PathToConfig = "Config/GameSettings.conf";		

		CScaleFactor ScaleFactor;
	};
}