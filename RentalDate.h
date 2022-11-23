#pragma once
#include <iostream>
#include <sstream>
using namespace std;

class RentalDate
{
public:
	RentalDate(const int d, const int m, const int y);
	RentalDate();
	~RentalDate();
	const string GetDate() const;
	
private:
	int d, m, y;
};

