#pragma once
#include "../IGameState.h"

namespace Arkanoid
{
	class SMainMenu : public IGameState
	{
	public:
		SMainMenu();
		~SMainMenu() = default;

		void Init() override;
		void EventUpdate(const sf::Event& Event) override;
		void GameplayUpdate(const float DeltaTime) override;
		void Draw(sf::RenderWindow& Window) override;

	private:

	};
}