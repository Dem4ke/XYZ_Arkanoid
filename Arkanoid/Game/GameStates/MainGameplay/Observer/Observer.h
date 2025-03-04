#pragma once

#include "../../../AppStates/AppStates.h"

namespace Arkanoid
{
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
		virtual bool IsGameplayTypeChanged() const = 0;
		virtual EGameplayType GetGameplayType() const = 0;
	};
}