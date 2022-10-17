#pragma once
#include "Vehicle.h"
class Bike : public Vehicle
{
public:

	Bike(string regNum, string make, string model, int age, int engineSize, int noWheels);
	~Bike();

	virtual double getCostPerDay() override;

	virtual void addVehicle() override;

	//void bikeSearch();

private:
	int roundEngineSize();

	int engineSize, noWheels;

};

