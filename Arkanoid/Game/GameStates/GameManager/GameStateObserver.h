#pragma once

namespace Arkanoid
{
	class IGameStateObserver
	{
	public:
		virtual ~IGameStateObserver() = default;
		virtual void GameStateClosed() = 0;
	};
}