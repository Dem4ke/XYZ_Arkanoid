#pragma once

#include "../../../AppStates/AppStates.h"
#include <vector>

namespace Arkanoid
{
	struct CGameState;

	// Interface of an observer
	class IBlockObserver
	{
	public:
		virtual ~IBlockObserver() = default;
		virtual void BlockBroken(int Cost) = 0;
	};

	class IBallObserver
	{
	public:
		virtual ~IBallObserver() = default;
		virtual void BallOut() = 0;
	};

	class IGameManager
	{
	public:
		virtual void SaveGameState(std::shared_ptr<CGameState> NewGameState) = 0;
		virtual std::shared_ptr<CGameState> GetGameState() = 0;

		virtual void ClearGameplayType() = 0;
		virtual bool IsGameplayTypeChanged() const = 0;
		virtual EGameplayType GetGameplayType() const = 0;
	};
}