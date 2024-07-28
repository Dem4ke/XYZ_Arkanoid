#pragma once

namespace SnakeGame {

	class Apple {
	public:
		Apple();

		void init(int cost = 2);
		void setStatus(bool isExists);
		void setPositionOnField(int position);

		int getPositionOnField() const;
		int getCost() const;
		bool isAppleExists() const;

	private:
		int positionOnField_ = 0;
		int cost_ = 0;

		bool isExists_ = false;
	};
}
