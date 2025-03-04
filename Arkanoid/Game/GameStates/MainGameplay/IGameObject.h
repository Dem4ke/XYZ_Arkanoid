#pragma once

#include <SFML/Graphics.hpp>
#include "../../AppStates/AppStates.h"

namespace Arkanoid
{
	// Interface of objects that used in main gameplay
	class IGameObject
	{
	public:
		virtual ~IGameObject() = default;

		virtual void Update(const float& DeltaTime) = 0;
		virtual void Draw(sf::RenderWindow& Window) = 0;
		virtual bool CheckCollision(std::shared_ptr<IGameObject> Object, EObjectType Type) = 0;
		virtual void Hit() = 0;

		virtual float GetOriginX() const = 0;
		virtual float GetOriginY() const = 0;
		virtual float GetWidth() const = 0;
		virtual float GetHeight() const = 0;

		virtual EObjectType GetObjectType() const = 0;
		virtual bool IsDestroyed() const = 0;
	};
}