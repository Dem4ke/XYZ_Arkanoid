#pragma once

namespace Arkanoid
{
	class IGameStateObserver
	{
	public:
		virtual ~IGameStateObserver() = default;
		virtual void GameStateChanged(int NewGameStateType) = 0;
	};
}