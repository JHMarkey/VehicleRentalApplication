#include "Rental.h"

Rental::Rental(Vehicle vehicle, int noDays) : vehicle(vehicle), noDays(noDays) {}
Rental::~Rental() {}

double Rental::CalcTotalCost() {
	return noDays * vehicle.getCostPerDay();
}