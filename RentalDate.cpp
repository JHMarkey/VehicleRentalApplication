#include "RentalDate.h"
#include <algorithm>

RentalDate::RentalDate() : d(1), m(1), y(2022) {}
RentalDate::RentalDate(const int d, const int m, const int y) : d(d), m(m), y(y) {}

RentalDate::~RentalDate(){}



const string RentalDate::GetDate() const {
	stringstream ss;	
	ss << d << "/" << m << "/" << y;
	return ss.str();
}

const int RentalDate::CalcDiff (const RentalDate* rhs)	const
{
	int yDif, mDif, dDif = 0, currentMonth, currentYear;
	yDif = y - rhs->y;													
	mDif = (yDif * 12) + (m - rhs->m);											

	currentYear = rhs->y;

	for (int i = 0; i < mDif; i++) {
		currentMonth = rhs->m + i;
		if (currentMonth > 12) currentMonth %= 12; currentYear++;
		dDif += DaysInMonth(currentMonth, currentYear);
	}

	
	return dDif + (d - rhs->d);
	
}

const int RentalDate::DaysInMonth(int m, int y) const {
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) return 31;
	else if (m == 2) {
		if (y % 4 == 0) {
			if (y % 100 == 0) {
				if (y % 400 == 0)	return 29;
				return 28;
			}
			return 29;
		}
		return 28;
	}
	else return 30;
}
