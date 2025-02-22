#pragma once

#include <SFML/Graphics.hpp>

namespace Arkanoid
{
	class IGameObject
	{
	public:
		virtual ~IGameObject() = default;

		virtual void Update(const float& DeltaTime) = 0;
		virtual void Draw(sf::RenderWindow& Window) = 0;

		virtual int CheckCollision(std::shared_ptr<IGameObject> Object) = 0;

		virtual float GetOriginX() const = 0;
		virtual float GetOriginY() const = 0;
		virtual float GetWidth() const = 0;
		virtual float GetHeight() const = 0;
	};
}