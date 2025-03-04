#pragma once

#include <memory>

namespace Arkanoid
{
	class IBlockObserver;
	class IBallObserver;

	// Interface of an observable subject
	class IBlockSubject
	{
	public:
		virtual void Attach(std::shared_ptr<IBlockObserver> Observer) = 0;
		virtual void Detach(std::shared_ptr<IBlockObserver> Observer) = 0;
		virtual void Notify() = 0;
	};

	class IBallSubject
	{
	public:
		virtual void Attach(std::shared_ptr<IBallObserver> Observer) = 0;
		virtual void Detach(std::shared_ptr<IBallObserver> Observer) = 0;
		virtual void Notify() = 0;
	};
}