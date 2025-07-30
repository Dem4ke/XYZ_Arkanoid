#pragma once

#include <memory>

namespace Arkanoid
{
	class IBlockObserver;
	class IBallObserver;
	class IBonusObserver;

	// Interface of an observable subject
	class IBlockSubject
	{
	public:
		virtual ~IBlockSubject() = default;

		virtual void Attach(std::weak_ptr<IBlockObserver> Observer) = 0;
		virtual void Detach(std::weak_ptr<IBlockObserver> Observer) = 0;
		virtual void Notify() = 0;
	};

	class IBallSubject
	{
	public:
		virtual ~IBallSubject() = default;

		virtual void Attach(std::weak_ptr<IBallObserver> Observer) = 0;
		virtual void Detach(std::weak_ptr<IBallObserver> Observer) = 0;
		virtual void Notify() = 0;
	};

	class IBonusSubject
	{
	public:
		virtual ~IBonusSubject() = default;

		virtual void Attach(std::weak_ptr<IBonusObserver> Observer) = 0;
		virtual void Detach(std::weak_ptr<IBonusObserver> Observer) = 0;
		virtual void Notify(bool bIsTaken) = 0;
	};
}