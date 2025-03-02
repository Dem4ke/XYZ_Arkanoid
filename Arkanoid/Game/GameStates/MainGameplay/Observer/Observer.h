#pragma once

#include "../IGameObject.h"

namespace Arkanoid
{
	// Interface of an observer
	class IObserver
	{
	public:
		virtual ~IObserver() = default;
		virtual void Update() = 0;
	};

	class BlocksObserver final : public IObserver
	{
	public:
		~BlocksObserver() = default;
		void Update() override;
	};

	class BallObserver final : public IObserver
	{

	};
}