#pragma once

namespace Arkanoid
{
	enum class EGameStateType : int
	{
		None = 0,

		// MENUS
		MainMenu,				// Main menu
		SettingsMenu,			// Menu of game settings
		LeaderBoardMenu,		// Leader board
		ExitMenu,				// Game closer menu
		// GAMEPLAY
		MainGameplay,			// Main gameplay
		// DIALOGS, POP UPS
		PauseDialog,			// Pause pop up
	};

	// Types of a settings menu
	enum class ESettingsType : int
	{
		Main = 0,	// Main settings
		Sounds,		// Sound settings
		Video,		// Video settings
	};
}