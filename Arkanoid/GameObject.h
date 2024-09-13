#pragma once

namespace ArkanoidGame {

	class GameObject {
	public:
		virtual ~GameObject() = default;

		virtual void init(float size, float speed) = 0;
		virtual void update(const float& deltaTime) = 0;
		virtual void draw() = 0;
	};
}