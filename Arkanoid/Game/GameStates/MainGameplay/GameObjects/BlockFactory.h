#pragma once

#include <SFML/Graphics.hpp>

namespace Arkanoid
{
	class IGameObject;

	class IBlockFactory
	{
	public:
		virtual ~IBlockFactory() = default;

		virtual std::shared_ptr<IGameObject> CreateBlock(const sf::Vector2f& Position) = 0;
	};

	class UNormalBlockFactory final : public IBlockFactory
	{
	public:
		UNormalBlockFactory() = default;
		~UNormalBlockFactory() = default;

		std::shared_ptr<IGameObject> CreateBlock(const sf::Vector2f& Position) override;
	};

	class UThreeHitBlockFactory final : public IBlockFactory
	{
	public:
		UThreeHitBlockFactory() = default;
		~UThreeHitBlockFactory() = default;

		std::shared_ptr<IGameObject> CreateBlock(const sf::Vector2f& Position) override;
	};

	class UUnbreakableBlockFactory final : public IBlockFactory
	{
	public:
		UUnbreakableBlockFactory() = default;
		~UUnbreakableBlockFactory() = default;

		std::shared_ptr<IGameObject> CreateBlock(const sf::Vector2f& Position) override;
	};
}