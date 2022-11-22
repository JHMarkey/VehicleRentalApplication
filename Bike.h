#pragma once
#include "Vehicle.h"
class Bike : public Vehicle
{
public:

	Bike(string regNum, string make, string model, int age, int engineSize, int noWheels);
	~Bike();

	virtual const double getCostPerDay() const override;

	virtual void addVehicle() override;

	


private:
	const int roundEngineSize() const;

	int engineSize, noWheels;

};

