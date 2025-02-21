#pragma once

#include <SFML/Graphics.hpp>

namespace Arkanoid
{
	class IGameObject
	{
	public:
		virtual ~IGameObject() = default;

		virtual void Init(float size, float speed, sf::Vector2f position) = 0;
		virtual void Update(const float& deltaTime) = 0;
		virtual void Draw() = 0;

		virtual int CheckCollision(std::shared_ptr<IGameObject> object) = 0;

		virtual float OriginX() const = 0;
		virtual float OriginY() const = 0;
		virtual float Width() const = 0;
		virtual float Height() const = 0;
	};
}