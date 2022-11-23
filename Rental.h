#pragma once
#include <iostream>
#include <string>
#include "Vehicle.h"
#include "RentalDate.h"

using namespace std;

struct Customer {
	string name, address, teleN;
};

class Rental
{

public:	
	Rental(const Vehicle* vehicle);
	~Rental();

	double CalcTotalCost();
	const int CalcNoDays() const;
	void CreateRentalFile();
	void AddRentalDetails();
	void DisplayRentalDetails();
	
	

private:
	const Customer CreateCustomer() const;
	const RentalDate* CreateStartDate() const;
	const RentalDate* CreateEndDate() const;
	string CreateRentalLine(string t);

	const Vehicle* vehicle;
	const RentalDate* start;
	const RentalDate* end;
	const int noDays;	
	const Customer customer;
	const char separator = ' ';

	template<typename T> const void printElement(T t, const int& width) const
	{
		cout << left << setw(width) << setfill(separator) << t;			
	}
};



