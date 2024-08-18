#include "Math.h"

namespace ArkanoidGame {
	bool IsCircleAndRectangleCollide(float radius, float circusCenterX, float circusBottomY, 
									 float rectTopLeftX, float rectTopRightX, float rectTopY) {
		if (circusBottomY >= rectTopY) {
			if ((circusCenterX ) >= rectTopLeftX &&
				(circusCenterX ) <= rectTopRightX) {

				return true;
			}
		}

		return false;
	}
}