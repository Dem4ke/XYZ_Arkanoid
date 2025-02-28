#pragma once

namespace Arkanoid
{
	enum class EGameStateType : int
	{
		None = 0,
		MainMenu,				// Main menu
		SettingsMenu,			// Menu of game settings
		LeaderBoardMenu,		// Leader board
		ExitMenu,				// Game closer menu
		MainGameplay,			// Main gameplay
		GameOver,				// Game over (win or lose)
	};

	// Types of a settings menu
	enum class ESettingsType : int
	{
		Main = 0,	// Main settings
		Sounds,		// Sound settings
		Video,		// Video settings
	};

	// Types of a sub gameplay states
	enum class EGameplayType : int
	{
		Main = 0,	// Main gameplay
		Pause,		// Pause dialog
		GameOver,	// Game over 
	};

	// Types of a game object's type
	enum class EObjectType : int
	{
		Ball = 0,
		Platform,
		SimpleBlock,
		ThreeHitBlock,
		UnbreackableBlock,
	};
}