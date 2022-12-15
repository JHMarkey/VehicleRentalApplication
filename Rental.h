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
	Rental(const Vehicle* vehicle, const string& name, const string& address, const string& teleN, const RentalDate* start, const RentalDate* end, const int noDays);
	~Rental();

	const double CalcTotalCost() const;
	const int CalcNoDays() const;	
	void CreateRentalFile();
	void AddRentalDetails();
	const void DisplayRentalDetails(int count) const;
	const static string CreateRentalLine(const string& t);

	const int GetNoDays() {
		return noDays;
	}

	const Vehicle* GetVehicle() {
		return vehicle;
	}

private:
	const Customer CreateCustomer() const;
	const Customer CreateCustomer(const string& name, const string& address, const string& teleN) const;
	const RentalDate* CreateStartDate() const;
	const RentalDate* CreateEndDate(const RentalDate* start) const;
	

	
	

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



