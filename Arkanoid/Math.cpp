#include "Math.h"

namespace ArkanoidGame {
	bool IsCircleAndRectangleCollide(float radius, float circusCenterX, float circusBottomY, 
									 float rectTopLeftX, float rectTopRightX, float rectTopY) {
		if (circusBottomY >= rectTopY) {
			if ((circusCenterX + radius) >= rectTopLeftX &&
				(circusCenterX - radius) <= rectTopRightX) {

				return true;
			}
		}

		return false;
	}
}