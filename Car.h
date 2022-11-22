#pragma once
#include "Vehicle.h"
class Car : public Vehicle
{
public:

	Car(string regNum, string make, string model, int age, int noDoors, int noSeats);
	~Car();

	virtual const double getCostPerDay() const override;

	virtual void addVehicle() override;

	//void carSearch();

	
	

private:

	

	int noDoors, noSeats;
};

