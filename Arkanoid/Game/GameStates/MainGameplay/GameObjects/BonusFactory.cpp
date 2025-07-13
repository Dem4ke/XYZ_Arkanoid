#include "BonusFactory.h"
#include "Bonus.h"

namespace Arkanoid
{
	std::shared_ptr<UBonus> UFireBallBonusFactory::CreateBonus(const sf::Vector2f& Position)
	{
		std::shared_ptr<UFireBallBonus> Bonus = std::make_shared<UFireBallBonus>(Position);
		return Bonus;
	}

	std::shared_ptr<UBonus> UGlassBlocksBonusFactory::CreateBonus(const sf::Vector2f& Position)
	{
		std::shared_ptr<UGlassBlocksBonus> Bonus = std::make_shared<UGlassBlocksBonus>(Position);
		return Bonus;
	}

	std::shared_ptr<UBonus> UBigPlatformBonusFactory::CreateBonus(const sf::Vector2f& Position)
	{
		std::shared_ptr<UBigPlatformBonus> Bonus = std::make_shared<UBigPlatformBonus>(Position);
		return Bonus;
	}
}