#include "RentalDate.h"

RentalDate::RentalDate() : d(1), m(1), y(2022) {}
RentalDate::RentalDate(const int d, const int m, const int y) : d(d), m(m), y(y) {}

RentalDate::~RentalDate(){}

const string RentalDate::GetDate() const {
	stringstream ss;	
	ss << d << "/" << m << "/" << y;
	return ss.str();
}