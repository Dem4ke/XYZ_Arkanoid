#pragma once
#include <string>

namespace Arkanoid
{
	class UGameSettings
	{
	public:
		static UGameSettings* GetGameSettings();

	private:
		UGameSettings();
		static UGameSettings* GameSettings;	// Pointer to only one UGameSettings object;

	private:
		int ScreenWidth = 0;				// Width of rendered window
		int ScreenHeight = 0;				// Height of rendered window

		float TimePerFrame = 0.f;			// Frame rate limit which user sets in settings
		float SoundPower = 0.f;				// Power of sounds in the game

		std::string PathToConfig;			// Path to config (settings) file
	};
}