#include "RentalDate.h"

RentalDate::RentalDate() : d(1), m(1), y(2022) {}
RentalDate::RentalDate(int d, int m, int y) : d(d), m(m), y(y) {}

RentalDate::~RentalDate(){}

string RentalDate::GetDate() {
	stringstream ss;	
	ss << d << "/" << m << "/" << y;
	return ss.str();
}