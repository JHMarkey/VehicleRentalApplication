#pragma once
#include "Vehicle.h"
class Bike : public Vehicle
{
public:

	Bike(const string regNum, const string make, const string model, const int age, const int engineSize, const int noWheels);
	~Bike();

	virtual const double getCostPerDay() const override;

	virtual void addVehicle() override;


private:
	const int roundEngineSize() const;

	int engineSize, noWheels;

};

