#pragma once

#include <memory>

namespace Arkanoid
{
	class IObserver;

	// Interface of an observable subject
	class ISubject
	{
	public:
		virtual void Attach(std::shared_ptr<IObserver> Observer) = 0;
		virtual void Detach(std::shared_ptr<IObserver> Observer) = 0;
		virtual void Notify() = 0;
	};
}