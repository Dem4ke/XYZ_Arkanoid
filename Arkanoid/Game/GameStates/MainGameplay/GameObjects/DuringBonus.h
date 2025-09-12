#pragma once

#include "../Observer/Subject.h"
#include <vector>

namespace Arkanoid
{
	// Class that contains bonus during timer
	class UDuringBonus : public IBonusSubject
	{
	public:
		UDuringBonus(int NumberInArray);
		~UDuringBonus() = default;

		void Attach(std::weak_ptr<IBonusObserver> Observer) override;
		void Detach(std::weak_ptr<IBonusObserver> Observer) override;
		void Notify(bool bIsTaken) override;

	private:
		int ArrayNumber = 0;									// Number of this item in bonuses array
		std::vector<std::weak_ptr<IBonusObserver>> Observers;	// Vector of observers
	};
}