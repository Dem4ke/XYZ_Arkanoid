#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

namespace Arkanoid
{
	struct CGameState;

	// Interface of an observer
	class IBlockObserver
	{
	public:
		virtual ~IBlockObserver() = default;
		virtual void BlockBroken(int Cost, const sf::Vector2f& Position) = 0;
	};

	class IBallObserver
	{
	public:
		virtual ~IBallObserver() = default;
		virtual void BallOut() = 0;
	};

	class IBonusObserver
	{
	public:
		virtual ~IBonusObserver() = default;
		virtual void BonusTaken(int Type) = 0;
	};
}