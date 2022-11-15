#pragma once
#include "Vehicle.h"
#include "RentalDate.h"

struct Customer {
	string name, address, teleN;
};

class Rental
{

public:	
	Rental(Vehicle vehicle, int  noDays);
	~Rental();

private:
	Vehicle vehicle;
	 
	int noDays;	
	Customer customer;
};



