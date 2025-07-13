#pragma once

#include <SFML/Graphics.hpp>

namespace Arkanoid
{
	class UBonus;

	class IBonusFactory
	{
	public:
		virtual ~IBonusFactory() = default;

		virtual std::shared_ptr<UBonus> CreateBonus(const sf::Vector2f& Position) = 0;
	};

	class UFireBallBonusFactory final : public IBonusFactory
	{
	public:
		UFireBallBonusFactory() = default;
		~UFireBallBonusFactory() = default;

		std::shared_ptr<UBonus> CreateBonus(const sf::Vector2f& Position) override;
	};

	class UGlassBlocksBonusFactory final : public IBonusFactory
	{
	public:
		UGlassBlocksBonusFactory() = default;
		~UGlassBlocksBonusFactory() = default;

		std::shared_ptr<UBonus> CreateBonus(const sf::Vector2f& Position) override;
	};

	class UBigPlatformBonusFactory final : public IBonusFactory
	{
	public:
		UBigPlatformBonusFactory() = default;
		~UBigPlatformBonusFactory() = default;

		std::shared_ptr<UBonus> CreateBonus(const sf::Vector2f& Position) override;
	};
}