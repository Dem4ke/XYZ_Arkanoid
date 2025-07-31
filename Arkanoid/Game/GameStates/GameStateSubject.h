#pragma once

#include <memory>

namespace Arkanoid
{
	class IGameStateObserver;

	class IGameStateSubject
	{
	public:
		virtual ~IGameStateSubject() = default;

		virtual void Attach(std::weak_ptr<IGameStateObserver> Observer) = 0;
		virtual void Detach(std::weak_ptr<IGameStateObserver> Observer) = 0;
		virtual void Notify(int NewGameStateType) = 0;
	};
}