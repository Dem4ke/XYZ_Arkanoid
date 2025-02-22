#include "BlockFactory.h"
#include "Block.h"

namespace Arkanoid
{
	std::shared_ptr<IGameObject> UNormalBlockFactory::CreateBlock(const sf::Vector2f& Position, const sf::Texture& Texture)
	{
		std::shared_ptr<UBlock> NormalBlock = std::make_shared<UBlock>(Position, Texture);
		return NormalBlock;
	}

	std::shared_ptr<IGameObject> UThreeHitBlockFactory::CreateBlock(const sf::Vector2f& Position, const sf::Texture& Texture)
	{
		std::shared_ptr<UThreeHitBlock> NormalBlock = std::make_shared<UThreeHitBlock>(Position, Texture);
		return NormalBlock;
	}

	std::shared_ptr<IGameObject> UUnbreakableBlockFactory::CreateBlock(const sf::Vector2f& Position, const sf::Texture& Texture)
	{
		std::shared_ptr<UUnbreakableBlock> NormalBlock = std::make_shared<UUnbreakableBlock>(Position, Texture);
		return NormalBlock;
	}
}