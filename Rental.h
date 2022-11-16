#pragma once
#include "Vehicle.h"
#include "RentalDate.h"

struct Customer {
	string name, address, teleN;
};

class Rental
{

public:	
	Rental(Vehicle vehicle, int noDays);
	~Rental();

	double CalcTotalCost();

private:
	Vehicle vehicle;
	RentalDate start;
	RentalDate end;
	int noDays;	
	Customer customer;
};



