#pragma once
#include <iostream>
#include "Vehicle.h"
#include "RentalDate.h"

using namespace std;

struct Customer {
	string name, address, teleN;
};

class Rental
{

public:	
	Rental(Vehicle* vehicle);
	~Rental();

	double CalcTotalCost();
	int CalcNoDays();
	void CreateRentalFile();
	void AddRentalDetails();
	void DisplayRentalDetails();
	
	

private:
	Customer CreateCustomer();
	RentalDate* CreateStartDate();
	RentalDate* CreateEndDate();
	string CreateRentalLine(string t);

	Vehicle* vehicle;
	RentalDate* start;
	RentalDate* end;
	int noDays;	
	Customer customer;
	const char separator = ' ';

	template<typename T> const void printElement(T t, const int& width) const
	{
		cout << left << setw(width) << setfill(separator) << t;			
	}
};



