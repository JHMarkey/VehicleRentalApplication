#pragma once
#include "Vehicle.h"
#include "Main.cpp"

class Rental
{
public:
	Rental(Vehicle vehicle, int  noDays, Customer customer);
	~Rental();

private:
	Vehicle vehicle;
	int noDays;	
};

