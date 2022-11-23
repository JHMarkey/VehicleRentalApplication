#pragma once
#include <iostream>
#include <sstream>
using namespace std;

class RentalDate
{
public:
	RentalDate(int d, int m, int y);
	RentalDate();
	~RentalDate();
	string GetDate();
	
private:
	int d, m, y;
};

