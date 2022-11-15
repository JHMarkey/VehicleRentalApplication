#pragma once
class RentalDate
{
public:
	RentalDate(int d, int m, int y) : d(d), m(m), y(y) {};
	~RentalDate() {};
private:
	int d, m, y;
};

