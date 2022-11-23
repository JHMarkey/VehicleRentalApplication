#pragma once
#include "Vehicle.h"
class Car : public Vehicle
{
public:

	Car(const string regNum, const string make, const string model, const int age, const int noDoors, const int noSeats);
	~Car();

	virtual const double getCostPerDay() const override;

	virtual void addVehicle() override;

	//void carSearch();
	
private:
	
	int noDoors, noSeats;
};

