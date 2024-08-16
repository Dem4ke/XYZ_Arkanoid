#include "Engine.h"

namespace ArkanoidGame {
	// Squares collision
	bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Vector2D rect2Size) {
		const float dx = fabs(rect1Position.x - rect2Position.x);
		const float dy = fabs(rect1Position.y - rect2Position.y);
		return (dx <= (rect1Size.x + rect2Size.x) / 2.f &&
			dy <= (rect1Size.y + rect2Size.y) / 2.f);
	}

	// Circus collision
	bool IsCircusCollide(Position2D circle1Position, float circle1Radius, Position2D circle2Position, float circle2Radius) {
		const float squareDistance = (circle1Position.x - circle2Position.x) * (circle1Position.x - circle2Position.x) +
			(circle1Position.y - circle2Position.y) * (circle1Position.y - circle2Position.y);
		const float squareRadiusSum = (circle1Radius + circle2Radius) * (circle1Radius + circle2Radius) / 4;
		return squareDistance <= squareRadiusSum;
	}
}