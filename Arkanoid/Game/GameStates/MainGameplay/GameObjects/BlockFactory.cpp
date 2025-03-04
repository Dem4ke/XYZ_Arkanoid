#include "BlockFactory.h"
#include "Block.h"
#include "../IGameObject.h"

namespace Arkanoid
{
	std::shared_ptr<UBlock> UNormalBlockFactory::CreateBlock(const sf::Vector2f& Position)
	{
		std::shared_ptr<UBlock> NormalBlock = std::make_shared<UBlock>(Position);
		return NormalBlock;
	}

	std::shared_ptr<UBlock> UThreeHitBlockFactory::CreateBlock(const sf::Vector2f& Position)
	{
		std::shared_ptr<UThreeHitBlock> ThreeHitBlock = std::make_shared<UThreeHitBlock>(Position);
		return ThreeHitBlock;
	}

	std::shared_ptr<UBlock> UUnbreakableBlockFactory::CreateBlock(const sf::Vector2f& Position)
	{
		std::shared_ptr<UUnbreakableBlock> UnbreakableBlock = std::make_shared<UUnbreakableBlock>(Position);
		return UnbreakableBlock;
	}
}