#pragma once
#include "Vehicle.h"
class Car : public Vehicle
{
public:

	Car(string regNum, string make, string model, int age, int noDoors, int noSeats);
	~Car();

	virtual double getCostPerDay() override;

	virtual void addVehicle() override;

	//void carSearch();

	

private:

	

	int noDoors, noSeats;
};

