#include "DuringBonus.h"
#include "../Observer/Observer.h"

namespace Arkanoid
{
	UDuringBonus::UDuringBonus(int NumberInArray)
		: ArrayNumber(NumberInArray) {}

	void UDuringBonus::Attach(std::weak_ptr<IBonusObserver> Observer)
	{
		Observers.push_back(Observer);
	}

	void UDuringBonus::Detach(std::weak_ptr<IBonusObserver> Observer)
	{

	}

	void UDuringBonus::Notify(bool bIsTaken)
	{
		for (auto& i : Observers)
		{
			i.lock()->BonusEnded(ArrayNumber);
		}
	}
}